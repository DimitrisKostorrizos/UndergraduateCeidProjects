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
  if (mySQLError != null) 
    console.log("MySQL Connection Error.");
  else
    console.log("Successful MySQL Connection.");
});

/**
 * Formats the @param timestampMs to MySQL date
 * @param {Timestamp in Milliseconds} timestampMs 
 */
function TimestampMsToMySQLDate(timestampMs)
{
  // Get the unformatted date representation of the timestampMs
  var unformattedDate = new Date(Number(timestampMs));

  // Format the date part to MySQL date
  var formattedDatePart = unformattedDate.toJSON().slice(0, 10);

  // Return the MySQL date
  return formattedDatePart;
}

async function GetQueryResult(databaseQuery) 
{
  return new Promise(data => {
    MySQLConnection.query(databaseQuery, function (error, result) 
    {
        if(error) 
        {
          throw error;
        }

        try 
        {
          data(result);
        } 
        catch (error) 
        {
          data({});
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
      bodyActivityCount++;
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


async function GetTop3Async()
{
  var data = await GetQueryResult("SELECT LocationsId, FirstName, LastName FROM users");

  var userScores = [];

  data.forEach(async row => 
  {
    var locationsId = row.LocationsId;
    
    var query = MySQLConnection.format("select InVehicle, OnBicycle, OnFoot, Running, Still, Tilting, Unknown, Walking from activities where ActivitiesId in(SELECT ActivitiesId FROM locations Where LocationId = ? AND ActivitiesId IS NOT null AND (MONTH(TimestampMs) - MONTH(CURDATE()) = 0))", locationsId);

    var activityData = await GetQueryResult(query);

    var ecoScore = GetEcoScore(activityData);

    // Add the monthly score
    userScores.push(
      {
        key : locationsId,
        value : [ecoScore, row.FirstName + " " + row.LastName[0] + "."]
      });
  });

  return userScores;
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
expressService.get("/admin/download", (requestObject, responseObject) => 
{

});

// The service for the admin analysis page
expressService.get("/admin/analysis", (requestObject, responseObject) => 
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

  // Parse the request body
  var userInfo = requestObject.body;

  // Get the locations id
  var locationsId = userInfo.locationsId;

  // Prepare the query
  var query = MySQLConnection.format("SELECT UploadDate FROM locations Where LocationId = ? Order By TimestampMs DESC Limit 1", locationsId);

  // Execute the query
  var results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["lastUploadDate"] = results[0].UploadDate.toJSON().slice(0, 10);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs FROM locations WHERE LocationId = ? ORDER BY TimestampMs ASC LIMIT 1", locationsId);

  // Execute the query
  results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["initialTimestampMS"] = results[0].TimestampMs.toJSON().slice(0, 10);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs FROM locations WHERE LocationId = ? ORDER BY TimestampMs DESC LIMIT 1", locationsId);

  // Execute the query
  results = await GetQueryResult(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["lastTimestampMS"] = results[0].TimestampMs.toJSON().slice(0, 10);

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

  var top = await GetTop3Async();

  // Get the top 3 users
  responseBody["top3"] = await GetTop3Async();
  
  // Set the response body
  responseObject.json(responseBody);
});

// The service for the user upload page
expressService.post("/user/upload", (requestObject, responseObject) => 
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
      // For every activity...
      for(const activity of location.activity) 
      {
        // Generate a unique id for the activity
        var activityId = uniqueIdGeneratorModule();

        // Get the timestamp
        var timestampMs = TimestampMsToMySQLDate(activity.timestampMs);
  
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
        
        // Execute the query
        MySQLConnection.query("Insert into activities values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", activityValues, function (mySQLError, result, fields) 
        {
          // If there was a MySQL error...
          if (mySQLError != null) 
            // Throw the error
            throw mySQLError;
        });
      }
    }
    // Get the location accuracy
    var accuracy = location.accuracy;

    // Get the location latitudeE7
    var latitudeE7 = location.latitudeE7;

    // Get the location longitudeE7
    var longitudeE7 = location.longitudeE7;

    // Get the location timestampMs
    var timestampMs = TimestampMsToMySQLDate(location.timestampMs);

    // Get the MySQL values
    var locationValues = [activityId, locationsId, accuracy, latitudeE7, longitudeE7, timestampMs];
    
    // Execute the query
    MySQLConnection.query("Insert into locations values (?, ?, ?, ?, ?, ?, CURDATE())", locationValues, function (mySQLError, result, fields) 
    {
      // If there was a MySQL error...
      if (mySQLError != null) 
        // Throw the error
        throw mySQLError;
    });
  }

  // Set the response body
  responseObject.json({validation: "Success"});
});

// The service for the user data page
expressService.get("/user/data", (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Parse the the json file
  var userInfo = requestObject.body;

  // Get the locations id query argument
  var locationsId = userInfo.locationsId;

  // Get the starting date query argument
  var startingDate = userInfo.startingDate;

  // Get the ending date query argument
  var endingDate = userInfo.endingDate;

  // Initialize an array that will contain the query values
  var queryValues = [locationsId];

  // Declare the MySQL statement
  var MySQLStatement = "select LatitudeE7, LongitudeE7 from locations where LocationId = ?";

  // If the starting date is not undefined...
  if(startingDate !== null)
  {
    // Add the new query value
    queryValues.push(startingDate);

    // Merge the MySQL statements
    MySQLStatement = MySQLStatement + ` AND datediff(TimestampMS, "${startingDate}") >= 0`;
  }

  // If the ending date is not undefined...
  if(endingDate !== null)
  {
    // Add the new query value
    queryValues.push(endingDate);

    // Merge the MySQL statements
    MySQLStatement = MySQLStatement + ` AND datediff(TimestampMS, "${endingDate}") <= 0`;
  }

  // Execute the query
  MySQLConnection.query(MySQLStatement, queryValues, function (mySQLError, result, fields) 
  {
    // If there was a MySQL error...
    if (mySQLError != null) 
      // Throw the error
      throw mySQLError;
    else
    {
      // If the result is not empty...
      if(result.length != 0)
      {
        // Set the body of the response
        responseObject.json({locations: result});
      }
    }
  });
});

// The service for the admin clear page
expressService.delete("/admin/clear", (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Execute the query
  MySQLConnection.query("Truncate locations", function (mySQLError, result, fields) 
  {
    // If there was a MySQL error...
    if (mySQLError != null) 
      // Throw the error
      throw mySQLError;
    else
    {
      MySQLConnection.query("Truncate activities", function (mySQLError, result, fields) 
      {
        // If there was a MySQL error...
        if (mySQLError != null) 
          // Throw the error
          throw mySQLError;
        else
        {
          MySQLConnection.query("Truncate users", function (mySQLError, result, fields) 
          {
            // If there was a MySQL error...
            if (mySQLError != null) 
              // Throw the error
              throw mySQLError;
            else
            {
              // Set the body of the response
              responseObject.json({status: "Success"});
            }
          });
        }
      });
    }
  });
});

// Start the express service
expressService.listen(port, function () 
{
  console.log(`Server is running on http://${host}:${port}`);
});
