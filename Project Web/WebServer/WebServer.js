// Get the url module
var urlModule = require('url');

// Get the MySQL driver module
var mysqlModule = require('mysql');

// Get the express module
var expressModule = require('express');

// Initialize the express service
var expressService = expressModule();

// Use the express json body parser
expressService.use(expressModule.json());

// Get the unique id generator module
const { v4: uniqueIdGeneratorModule } = require('uuid');

// Create the MySQL connection
var MySQLConnection = mysqlModule.createConnection({
  host: "localhost",
  user: "root",
  password: "root",
  database: "locationsdb"
});

// Try to connect to the MySQL database
MySQLConnection.connect(function(mySQLError) 
{
  // If there was a connection error...
  if (mySQLError != null) 
    console.log("MySQL Connection Error.");
  else
    console.log("Successful MySQL Connection.");
});

/**
 * Returns the MySQL date part of @param value
 * @param {TimestampMS} value 
 */
function GetMySQLDatePart(value)
{
  return value.toJSON().slice(0, 10);
}

/**
 * Returns the MySQL time part of @param value
 * @param {TimestampMS} value 
 */
function GetMySQLTimePart(value)
{
  return value.toJSON().slice(11, 19);
}

/**
 * Returns the MySQL datetime part of @param value
 * @param {TimestampMS} value 
 */
function GetMySQLDateTimePart(value)
{
  return GetMySQLDatePart(value) + " " + GetMySQLTimePart(value);
}

/**
 * Formats the @param timestampMs to MySQL datetime
 * @param {Timestamp in Milliseconds} timestampMs 
 */
function TimestampMsToMySQLDateTime(timestampMs)
{
  // Get the unformatted date representation of the timestampMs
  var unformattedDate = new Date(Number(timestampMs));

  // Format the date part to MySQL date
  var formattedDatePart = GetMySQLDateTimePart(unformattedDate);

  // Return the MySQL date
  return formattedDatePart;
}

/**
 * Executes and returns the result of @param MySQLQuery asynchronously
 * @param {MySQL query} MySQLQuery 
 */
async function GetQueryResult(MySQLQuery) 
{
  // Return the query's execution result, wrapped in a promise object
  return new Promise(data => {
    // Execute the query
    MySQLConnection.query(MySQLQuery, function (error, result) 
    {
      // If there was an error...
      if(error) 
      {
        // Throw the error
        throw error;
      }

      // Try to return the results
      try 
      {
        // Return an array that contains the results
        data(result);
      } 
      catch (error) 
      {
        // Return empty array
        data({});

        // Trow the error
        throw error;
      }
    });
  });
}

/**
 * Calculates the eco score based on the @param activityData
 * @param {[ActivityRow]} activityData 
 */
function GetEcoScore(activityData)
{
  // Initialize a counter
  var bodyActivityCounter = 0;
  
  // For every row in the result...
  for(const row of activityData)
  {
    // If the activity counts a a body type activity...
    if(row.InVehicle < Math.max(row.OnBicycle, row.OnFoot, row.Walking, row.Running))
      // Increase the counter
      bodyActivityCounter++;
  }
  // If there are monthly activities...
  if(activityData.length != 0)
    // Calculate the % percentage
    var bodyActivityPercentage = Math.round(bodyActivityCounter / activityData.length) * 100;
  else
    // Set the percentage to 0
    var bodyActivityPercentage = 0;

  // Return the % representation of the percentage 
  return bodyActivityPercentage + " %";
}

/**
 * Calculates and returns the user ranking entry
 * @param {[LocationsId, FirstName, LastName]]} userInfo 
 */
async function GetUserRanking(userInfo)
{
  // Get the locations id
  var locationsId = userInfo.LocationsId;
  
  // Prepare the query
  var query = MySQLConnection.format("select InVehicle, OnBicycle, OnFoot, Running, Still, Tilting, Unknown, Walking from activities where ActivitiesId in(SELECT ActivitiesId FROM locations Where LocationId = ? AND ActivitiesId IS NOT null AND (MONTH(TimestampMs) - MONTH(CURDATE()) = 0))", locationsId);

  // Get the user's activity data
  var activityData = await GetQueryResult(query);

  // Get the user's eco score
  var ecoScore = GetEcoScore(activityData);

  // Initialize the user ranking
  var userRanking = 
  {
    locationsId : locationsId,
    ecoScore : ecoScore, 
    abbreviatedFullName : userInfo.FirstName + " " + userInfo.LastName[0] + "."
  }

  // Return user ranking
  return userRanking;
}

/**
 * Insert the activities that are associated with the @param location into tha database
 * @param {location} location 
 */
async function InsertLocationsActivity(location)
{
  // Generate a unique id for the activity
  var activityId = uniqueIdGeneratorModule();

  // For every activity...
  for(const activity of location.activity)
  {
    // Get the timestamp
    var timestampMs = TimestampMsToMySQLDateTime(activity.timestampMs);

    // Initialize the dictionary for the activity types
    var activitiesDictionary = 
    {
      "IN_VEHICLE" : 0, 
      "ON_BICYCLE": 0, 
      "ON_FOOT" : 0, 
      "RUNNING" : 0, 
      "STILL" : 0, 
      "TILTING" : 0, 
      "UNKNOWN" : 0,  
      "WALKING" : 0
    };

    // For every activity type...
    for(const activityType of activity.activity) 
    {
      // Get the type
      var type = activityType.type;

      // If the type is a key in the dictionary...
      if((type in activitiesDictionary))
        // Set the type's confidence
        activitiesDictionary[type] = activityType.confidence;
    }

    // Get the MySQL values
    var activityValues = 
    [activityId, timestampMs, activitiesDictionary["IN_VEHICLE"], activitiesDictionary["ON_BICYCLE"], 
    activitiesDictionary["ON_FOOT"], activitiesDictionary["RUNNING"], activitiesDictionary["STILL"], 
    activitiesDictionary["TILTING"],activitiesDictionary["UNKNOWN"],activitiesDictionary["WALKING"]];
    
    // Prepare the query
    var query = MySQLConnection.format("INSERT INTO activities VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", activityValues);

    // Execute the query
    await GetQueryResult(query);
  }

  // Return the activity id
  return activityId;
}

/**
 * Calculates and returns an array that contain the top 3 users, based on the monthly eco score
 */
async function GetTop3Async()
{
  // Get the users
  var users = await GetQueryResult("SELECT LocationsId, FirstName, LastName FROM users");

  // Declare an array tht will contain the top 3 users
  var userScores = [];

  // For every user...
  for(const user of users) 
  {
    userScores.push(await GetUserRanking(user));
  }

  // Descending sort the users based on the eco score
  userScores.sort((a, b) =>
  {
    if (a.ecoScore < b.ecoScore) 
      return -1;

    if (a.ecoScore > b.ecoScore) 
      return 1;

    return 0;
  });

  // Return the 3 top users
  return userScores.slice(0,3);
}

// Set the host name
const host = 'localhost';

// Set the web server port
const port = 8080;

// The service for the admin dashboard page
expressService.get("/admin/dashboard", async (requestObject, responseObject) => 
{

});

// The service for the admin download page
expressService.get("/admin/download", async (requestObject, responseObject) => 
{

});

// The service for the admin analysis page
expressService.get("/admin/analysis", async (requestObject, responseObject) => 
{

});

// The service for the login page
expressService.get("/login", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Initialize the response body
  var responseBody = 
  {
    validation : false,
    locationsId : null,
    userId : null
  };

  // Parse the request body
  var userInfo = requestObject.body;

  // Get the username value
  var username = userInfo.username;

  // Get the password value
  var password = userInfo.password;

  // Prepare the MySQL query
  var query = MySQLConnection.format("SELECT HashedPassword, UserId, LocationsId, UserId FROM users WHERE Username = ?", username);

  // Get the query results
  var results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
  {
    // Get the hashed password
    var hashedPassword = results[0].HashedPassword;

    // Get the locations id
    var locationsId = results[0].LocationsId;

    // Get the user id
    var userId = results[0].UserId;

    // Check if the password is correct...
    if(hashedPassword == password)
    {
      // Set the body fof the response
      responseBody["locationsId"] = locationsId;
      responseBody["userId"] = locationsId;
      responseBody["validation"] = true;
    }
  }
  responseObject.json(responseBody);
});

// The service for the sign up page
expressService.post("/signup", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Initialize the response body
  var responseBody = 
  {
    locationsId : null,
    userId : null
  }; 

  // Parse the request body
  var userInfo = requestObject.body;

  // Get the username
  var username = userInfo.username;

  // Get the hashed password
  var hashedPassword = userInfo.hashedPassword;

  // Get the username query argument
  var firstName = userInfo.firstName;

  // Get the password query argument
  var lastName = userInfo.lastName;

  // Generate a unique locations id 
  var locationsId = uniqueIdGeneratorModule();

  // Generate a unique user id 
  var userId = uniqueIdGeneratorModule();

  // Prepare the query
  var query = MySQLConnection.format("INSERT INTO users VALUES (?, ?, ?, ?, ?, ?)", [userId, locationsId, username, hashedPassword, firstName, lastName]);
  
  // Execute the query
  await GetQueryResult(query);

  // Set the response body
  responseBody["locationsId"] = locationsId;
  responseBody["userId"] = userId;

  // Set the body of the response
  responseObject.json(responseBody);
});

// The service for the user info page
expressService.get("/user/info", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Initialize the response body
  var responseBody = 
  {
    lastUploadDate : null,
    initialTimestampMS : null,
    lastTimestampMS : null,
    ecoScores : [],
    top3 : []
  }; 

  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the user id query argument
  var locationsId = queryArguments.locationsId;

  // Prepare the query
  var query = MySQLConnection.format("SELECT UploadDate FROM locations Where LocationId = ? Order By TimestampMs DESC Limit 1", locationsId);

  // Execute the query
  var results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["lastUploadDate"] = GetMySQLDatePart(results[0].UploadDate);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs FROM locations WHERE LocationId = ? ORDER BY TimestampMs ASC LIMIT 1", locationsId);

  // Execute the query
  results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["initialTimestampMS"] = GetMySQLDatePart(results[0].TimestampMs);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs FROM locations WHERE LocationId = ? ORDER BY TimestampMs DESC LIMIT 1", locationsId);

  // Execute the query
  results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["lastTimestampMS"] = GetMySQLDatePart(results[0].TimestampMs);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs, InVehicle, OnBicycle, OnFoot, Running, Still, Tilting, Unknown, Walking FROM activities WHERE ActivitiesId in (SELECT ActivitiesId FROM locations WHERE LocationId = ? AND ActivitiesId IS NOT NULL AND datediff(TimestampMs, CURDATE()) > -366 ORDER BY TimestampMs ASC)", locationsId);

  // Execute the query
  results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
  {
    for(var month = 0; month < 12; month++)
    {
      // Get the monthly results
      var monthlyActivityData = results.filter(x => x.TimestampMs.getMonth() == month);

      // Calculate the monthly eco score
      var ecoScore = GetEcoScore(monthlyActivityData);

      // Add the monthly score
      responseBody["ecoScores"].push(
        {
          key : month,
          value : ecoScore
        });
    }
  }

  // Get the top 3 users
  responseBody["top3"] = await GetTop3Async();
  
  // Set the response body
  responseObject.json(responseBody);
});

// The service for the user upload page
expressService.post("/user/upload", async(requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);
  
  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the user id query argument
  var locationsId = queryArguments.locationsId;

  // Parse the the json file
  var jsonData = requestObject.body;

  // For every location int the json...
  for(const location of jsonData.locations)
  {
    // Initialize the activity id
    var activityId = null;

    // If the type is a key in the dictionary...
    if(location.hasOwnProperty("activity"))
    {
      // Generate a unique id for the activity
      var activityId = await InsertLocationsActivity(location);
    }
    // Get the location accuracy
    var accuracy = location.accuracy;

    // Get the location latitudeE7
    var latitudeE7 = location.latitudeE7;

    // Get the location longitudeE7
    var longitudeE7 = location.longitudeE7;

    // Get the location timestampMs
    var timestampMs = TimestampMsToMySQLDateTime(location.timestampMs);

    // Get the MySQL values
    var locationValues = [activityId, locationsId, accuracy, latitudeE7, longitudeE7, timestampMs];
    
    // Prepare the query
    var query = MySQLConnection.format("INSERT INTO locations VALUES (?, ?, ?, ?, ?, ?, CURDATE())", locationValues);

    // Execute the query
    await GetQueryResult(query);
  }

  // Set the response body
  responseObject.json({status: true});
});

// The service for the user data page
expressService.get("/user/data", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the locations id query argument
  var locationsId = queryArguments.locationsId;

  // Get the starting date query argument
  var startingDate = queryArguments.startingDate;

  // Get the ending date query argument
  var endingDate = queryArguments.endingDate;

  // Initialize an array that will contain the query values
  var queryValues = [locationsId];

  // Declare the MySQL statement
  var query = "SELECT LatitudeE7, LongitudeE7 FROM locations WHERE LocationId = ?";

  // If the starting date is not undefined...
  if(startingDate !== null)
  {
    // Add the new query value
    queryValues.push(startingDate);

    // Merge the queries
    query = query + ` AND datediff(TimestampMS, "${startingDate}") >= 0`;
  }

  // If the ending date is not undefined...
  if(endingDate !== null)
  {
    // Add the new query value
    queryValues.push(endingDate);

    // Merge the queries
    query = query + ` AND datediff(TimestampMS, "${endingDate}") <= 0`;
  }

  // Prepare the query
  query = MySQLConnection.format(query, queryValues)

  // Execute the query
  var results = await GetQueryResult(query);
  
   // If the result is not empty...
   if(results.length != 0)
   {
     // Set the body of the response
     responseObject.json({locations: results});
   }
});

// The service for the admin clear page
expressService.delete("/admin/clear", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  //Prepare the query
  var query = MySQLConnection.format("Truncate locations");

  // Execute the query
  await GetQueryResult(query);

  //Prepare the query
  query = MySQLConnection.format("Truncate activities");

  // Execute the query
  await GetQueryResult(query);

  //Prepare the query
  query = MySQLConnection.format("Truncate users");

  // Execute the query
  await GetQueryResult(query);

  // Set the body of the response
  responseObject.json({status: true});
});

// Start the express service
expressService.listen(port, function () 
{
  console.log(`Server is running on http://${host}:${port}`);
});
