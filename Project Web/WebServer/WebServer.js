// Get the url module
var urlModule = require('url');

// Get the MySQL driver module
var mysqlModule = require('mysql');

// Get the cors module
const cors = require('cors');

// Get the express module
const expressModule = require('express');

// Initialize the express service
const expressService = expressModule();

// Use cors module
expressService.use(cors());

// Use the express json body parser
expressService.use(expressModule.json({ limit: '1gb' }));

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
 * @param {TimestampMs} value 
 */
function GetMySQLDatePart(value)
{
  return value.toJSON().slice(0, 10);
}

/**
 * Returns the MySQL time part of @param value
 * @param {TimestampMs} value 
 */
function GetMySQLTimePart(value)
{
  return value.toJSON().slice(11, 19);
}

/**
 * Returns the MySQL datetime part of @param value
 * @param {TimestampMs} value 
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
 * Calculates and return the @param activities percentage
 * @param {Activities} activities 
 */
function GetActivitiesPercentage(activities)
{
  // Initialize the dictionary that will contain the activity type percentages
  var activityTypeCounterDictionary =
  {
   InVehicle : 0, 
   OnBicycle : 0, 
   OnFoot : 0, 
   Running : 0, 
   Still : 0, 
   Tilting : 0, 
   Unknown : 0,
   Walking : 0
  };

  // For every activity...
  for(const activity of activities)
  {
    // For every activity type...
    for(const activityType in activityTypeCounterDictionary)
    {
      // If the activity value is not 0...
      if(activity[activityType] != 0)
        // Count the activity type
        activityTypeCounterDictionary[activityType]++;
    }
  }

  // For every type...
  for(const activityType in activityTypeCounterDictionary)
  {
    // Calculate the type percentage
    activityTypeCounterDictionary[activityType] = activityTypeCounterDictionary[activityType] / activities.length * 100;
  }

  // Return the dictionary
  return activityTypeCounterDictionary;
}

/**
 * Calculates and return the hour of the day that has the most @param activities entries
 * @param {Activities} activities 
 */
function GetHourPerActivity(activities)
{
  // Initialize the dictionary that will contain the activity type hours
  var activityTypeHourDictionary =
  {
   InVehicle : null, 
   OnBicycle : null, 
   OnFoot : null, 
   Running : null, 
   Still : null, 
   Tilting : null, 
   Unknown : null,
   Walking : null
  };

  // For every activity type...
  for(const activityType in activityTypeHourDictionary)
  {
    // Get the activities that have non zero value for the selected type
    var filteredActivities = activities.filter(x => x[activityType] != 0);

    // Initialize an array that will contain the count of the activities grouped by hour
    var hoursDictionary = [];

    // For every hour...
    for(var hour = 0; hour < 24; hour++)
    {
      // Get the activities that have non zero value for the selected type
      var filteredByHourActivities = filteredActivities.filter(x => x.TimestampMs.getHours() == hour);

      // Add the entry
      hoursDictionary.push(filteredByHourActivities.length);
    }

    // Get the max value
    var maxValue = hoursDictionary.reduce(function(a, b) 
    {
      return Math.max(a, b);
    });

    // Get the index of the max value
    activityTypeHourDictionary[activityType] = hoursDictionary.indexOf(maxValue);
  }

  // Return the dictionary
  return activityTypeHourDictionary;
}

/**
 * Calculates and return the the day of the week that has the most @param activities entries
 * @param {Activities} activities 
 */
function GetDayPerActivity(activities)
{
  // Initialize the dictionary that will contain the activity type hours
  var activityTypeDayDictionary =
  {
   InVehicle : null, 
   OnBicycle : null, 
   OnFoot : null, 
   Running : null, 
   Still : null, 
   Tilting : null, 
   Unknown : null,
   Walking : null
  };

  // For every activity type...
  for(const activityType in activityTypeDayDictionary)
  {
    // Get the activities that have non zero value for the selected type
    var filteredActivities = activities.filter(x => x[activityType] != 0);

    // Initialize an array that will contain the count of the activities grouped by day
    var daysDictionary = [];

    // For every day...
    for(var day = 0; day < 7; day++)
    {
      // Get the activities that have non zero value for the selected type
      var filteredByHourActivities = filteredActivities.filter(x => x.TimestampMs.getDay() == day);

      // Add the entry
      daysDictionary.push(filteredByHourActivities.length);
    }

    // Get the max value
    var maxValue = daysDictionary.reduce(function(a, b) 
    {
      return Math.max(a, b);
    });

    // Get the index of the max value
    activityTypeDayDictionary[activityType] = daysDictionary.indexOf(maxValue);
  }

  // Return the dictionary
  return activityTypeDayDictionary;
}

/**
 * Calculates and return the activities per month percentage
 * @param {[ActivitiesResults]} activitiesResults 
 */
function GetActivitiesPerMonthPercentage(activitiesResults)
{
  // Declare an array that will contain the users' activities percentages
  var monthsArray = [];

  // For every user...
  for(var month = 0; month < 12; month++)
  {
    // Get the monthly results 
    var monthlyResults = activitiesResults.filter(x => x.TimestampMs.getMonth() == month);

    // If there is at least one result...
    if(monthlyResults.length != 0)
    {
      // Add the monthly activities percentage
      monthsArray.push(
        {
          "month" : month,
          "activities" : GetActivitiesPercentage(monthlyResults)
        });
    }
    else
    {
      // Add the monthly activities percentage
      monthsArray.push(
        {
          "month" : month,
          "activities" : null
        });
    }
  }

  // Return the array
  return monthsArray
};

/**
 * Calculates and return the activities per hour percentage
 * @param {[ActivitiesResults]} activitiesResults 
 */
function GetActivitiesPerHourPercentage(activitiesResults)
{
  // Declare an array that will contain the users' activities percentages
  var hoursArray = [];

  // For every user...
  for(var hour = 0; hour < 24; hour++)
  {
    // Get the hourly results 
    var hourlyResults = activitiesResults.filter(x => x.TimestampMs.getHours() == hour);

    // If there is at least one result...
    if(hourlyResults.length != 0)
    {
      // Add the hourly activities percentage
      hoursArray.push(
        {
          "hour" : hour,
          "activities" : GetActivitiesPercentage(hourlyResults)
        });
    }
    else
    {
      // Add the hourly activities percentage
      hoursArray.push(
        {
          "hour" : hour,
          "activities" : null
        });
    }
  }

  // Return the array
  return hoursArray
};

/**
 * Calculates and return the activities per week day percentage
 * @param {[ActivitiesResults]} activitiesResults 
 */
function GetActivitiesPerWeekDayPercentage(activitiesResults)
{
  // Declare an array that will contain the users' activities percentages
  var weekDayArray = [];

  // For every user...
  for(var weekDay = 0; weekDay < 7; weekDay++)
  {
    // Get the daily results 
    var weekDayResults = activitiesResults.filter(x => x.TimestampMs.getDay() == weekDay);

    // If there is at least one result...
    if(weekDayResults.length != 0)
    {
      // Add the daily activities percentage
      weekDayArray.push(
        {
          "weekDay" : weekDay,
          "activities" : GetActivitiesPercentage(weekDayResults)
        });
    }
    else
    {
      // Add the daily activities percentage
      weekDayArray.push(
        {
          "weekDay" : weekDay,
          "activities" : null
        });
    }
  }

  // Return the array
  return weekDayArray
};

/**
 * Calculates and return the activities per year percentage
 * @param {[ActivitiesResults]} activitiesResults 
 */
function GetActivitiesPerYearPercentage(activitiesResults)
{
  // Declare an array that will contain the users' activities percentages
  var yearArray = [];

  // Get the current year
  var currentYear = new Date().getFullYear();

  // Ascending sort the activities results based on the year
  activitiesResults.sort(function(a, b) 
  {
    if(a.TimestampMs.getFullYear() >= b.TimestampMs.getFullYear())
      return a;

    if(a.TimestampMs.getFullYear() < b.TimestampMs.getFullYear())
      return b;
  });

  // Get the minimum year
  var minimumYear = activitiesResults[0].TimestampMs.getFullYear();

  // For every user...
  for(var year = minimumYear; year <= currentYear; year++)
  {
    // Get the daily results 
    var yearResults = activitiesResults.filter(x => x.TimestampMs.getFullYear() == year);

    // If there is at least one result...
    if(yearResults.length != 0)
    {
      // Add the daily activities percentage
      yearArray.push(
        {
          "year" : year,
          "activities" : GetActivitiesPercentage(yearResults)
        });
    }
    else
    {
      // Add the daily activities percentage
      yearArray.push(
        {
          "year" : year,
          "activities" : null
        });
    }
  }

  // Return the array
  return yearArray
};

/**
 * Executes and returns the result of @param MySQLQuery asynchronously
 * @param {MySQL query} MySQLQuery 
 */
async function GetQueryResultAsync(MySQLQuery) 
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
  return bodyActivityPercentage;
}

/**
 * Calculates and returns the user ranking entry
 * @param {[LocationId, FirstName, LastName]]} userInfo 
 */
async function GetUserRankingAsync(userInfo)
{
  // Get the location id
  var locationId = userInfo.LocationId;
  
  // Prepare the query
  var query = MySQLConnection.format("SELECT InVehicle, OnBicycle, OnFoot, Running, Still, Tilting, Unknown, Walking from activities where ActivitiesId in(SELECT ActivitiesId FROM locations Where LocationId = ? AND ActivitiesId IS NOT null AND (MONTH(TimestampMs) - MONTH(CURDATE()) = 0))", locationId);

  // Get the user's activity data
  var activityData = await GetQueryResultAsync(query);

  // Get the user's eco score
  var ecoScore = GetEcoScore(activityData);

  // Initialize the user ranking
  var userRanking = 
  {
    locationId : locationId,
    ecoScore : ecoScore, 
    abbreviatedFullName : userInfo.FirstName + " " + userInfo.LastName[0] + "."
  }

  // Return user ranking
  return userRanking;
}

/**
 * Calculates and return the activities per user percentage
 * @param {UserResults} userResults 
 * @param {[ActivitiesResults]} activitiesResults 
 */
async function GetActivitiesPerUserPercentageAsync(userResults, activitiesResults)
{
  // Declare an array that will contain the users' activities percentages
  var usersArray = [];

  // For every user...
  for(const user of userResults)
  {
    // Prepare the MySQL query
    var activitiesIdQuery = MySQLConnection.format("SELECT ActivitiesId FROM locations where LocationId = ?", user.LocationId);

    // Get the query results
    var activitiesIdsResults = await GetQueryResultAsync(activitiesIdQuery);

    // If there is at least one result...
    if(activitiesIdsResults.length != 0)
    {
      // Get the selected user activities
      activitiesResults.filter(x => activitiesIdsResults.includes(x.ActivitiesId));

      // Get the activities percentage
      usersArray.push(
        {
          "User" : user.Username,
          "Activities" : GetActivitiesPercentage(activitiesResults)
        });
    }
    else
    {
      // Get the activities percentage
      usersArray.push(
        {
          "User" : user.Username,
          "Activities" : null
        });
    }
  }
  // Return the array
  return usersArray;
}

/**
 * Insert the activities that are associated with the @param location into tha database
 * @param {location} location 
 */
async function InsertLocationsActivityAsync(location)
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
    var query = MySQLConnection.format("INSERT INTO activities(ActivitiesId, TimestampMs, InVehicle, OnBicycle, OnFoot, Running, Still, Tilting, Unknown, Walking) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", activityValues);

    // Execute the query
    await GetQueryResultAsync(query);
  }

  // Return the activity id
  return activityId;
}

/**
 * Calculates and returns an array that contain the top 3 users, based on the monthly eco score
 */
async function GetTop3Async(userLocationId)
{
  // Get the users
  var users = await GetQueryResultAsync("SELECT LocationId, FirstName, LastName FROM users");

  // Declare an array tht will contain the top 3 users
  var userScores = [];

  // For every user...
  for(const user of users) 
  {
    // Add the user ranking
    userScores.push(await GetUserRankingAsync(user));
  }

  // Descending sort the users based on the eco score
  userScores.sort((a, b) =>
  {
    if (a.ecoScore < b.ecoScore) 
      return 1;

    if (a.ecoScore > b.ecoScore) 
      return -1;

    return 0;
  });

  // Get the 3 top users
  var top3Users = userScores.slice(0,3);

  // Add the current user position
  top3Users.push(userScores.filter(x => x.locationId == userLocationId)[0]);

  // Return the 3 top users
  return top3Users;
}

// Set the host name
const host = 'localhost';

// Set the web server port
const port = 8080;

// The service for the admin dashboard page
expressService.get("/admin/dashboard", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Initialize the response body
  var responseBody = 
  {
    activitiesPercentage : [],
    activitiesPerUserPercentage : [],
    activitiesPerMonthPercentage : [],
    activitiesPerWeekDayPercentage : [],
    activitiesPerHourPercentage : [],
    activitiesPerYearPercentage : []
  };

  // Prepare the MySQL query
  var activitiesQuery = MySQLConnection.format("SELECT * FROM activities");

  // Get the query results
  var activitiesResults = await GetQueryResultAsync(activitiesQuery);

  // If there is at least one result...
  if(activitiesResults.length != 0)
  {
    // Get the activities percentage
    responseBody["activitiesPercentage"] = GetActivitiesPercentage(activitiesResults);

    // Prepare the MySQL query
    var usersQuery = MySQLConnection.format("SELECT Username, LocationId FROM users");

    // Get the query results
    var userResults = await GetQueryResultAsync(usersQuery);

    // If there is at least one result...
    if(userResults.length != 0)
    {
      // Get the activities per user percentage
      responseBody["activitiesPerUserPercentage"] = await GetActivitiesPerUserPercentageAsync(userResults, activitiesResults);
    }

    // Get the activities per month percentage
    responseBody["activitiesPerMonthPercentage"] = GetActivitiesPerMonthPercentage(activitiesResults);
    
    // Get the activities per month percentage
    responseBody["activitiesPerHourPercentage"] = GetActivitiesPerHourPercentage(activitiesResults);

    // Get the activities per week day percentage
    responseBody["activitiesPerWeekDayPercentage"] = GetActivitiesPerWeekDayPercentage(activitiesResults);
    
    // Get the activities per year percentage
    responseBody["activitiesPerYearPercentage"] = GetActivitiesPerYearPercentage(activitiesResults);
  }

  // Set the response body
  responseObject.json(responseBody);
});

// The service for the admin analysis page
expressService.get("/admin/analysis", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Initialize the response body
  var responseBody = 
  {
    locations : []
  };

  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the starting year query argument
  var startingYear = queryArguments.startingYear;

  // Get the ending year query argument
  var endingYear = queryArguments.endingYear;

  // Get the starting month query argument
  var startingMonth = queryArguments.startingMonth;

  // Get the ending month query argument
  var endingMonth = queryArguments.endingMonth;

  // Get the starting day query argument
  var startingDay = queryArguments.startingDay;

  // Get the ending day query argument
  var endingDay = queryArguments.endingDay;

  // Get the starting time query argument
  var startingTime = queryArguments.startingTime;

  // Get the ending time query argument
  var endingTime = queryArguments.endingTime;

  // Get the activities types query argument
  var activitiesTypes = queryArguments.activitiesType;  
  
  // Initialize the query
  var locationsQuery = "SELECT LatitudeE7, LongitudeE7 FROM locations";

  // Declare an array that will contain the query values
  var queryValues = [];

  // If there is at least one query argument...
  if(Object.keys(queryArguments).length != 0)
  {
    // Calculate the number of ands in the query
    var numberOfAnds = (Object.keys(queryArguments).length - 1) / 2 - 1;

    // Merge the queries
    locationsQuery = locationsQuery + " WHERE (";

    // If a timespan has been selected...
    if(startingYear !== null && endingYear !== null)
    {
      // Add the staring year
      queryValues.push(startingYear);

      // Add the ending year
      queryValues.push(endingYear);

      // Merge the queries
      locationsQuery = locationsQuery + " YEAR(TimestampMs) BETWEEN ? AND ?";
    }

    // If an "AND" must be added...
    if(numberOfAnds != 0)
    {
      // Merge the queries
      locationsQuery = locationsQuery + " AND";

      // Reduce the counter
      numberOfAnds--;
    }

    // If a timespan has been selected...
    if(startingDay !== null && endingDay !== null)
    {
      // Add the staring month
      queryValues.push(startingDay);

      // Add the ending month
      queryValues.push(endingDay);

      // Merge the queries
      locationsQuery = locationsQuery + " DAY(TimestampMs) BETWEEN ? AND ?";
    }

    // If an "AND" must be added...
    if(numberOfAnds != 0)
    {
      // Merge the queries
      locationsQuery = locationsQuery + " AND";

      // Reduce the counter
      numberOfAnds--;
    }

    // If a timespan has been selected...
    if(startingMonth !== null && endingMonth !== null)
    {
      // Add the staring month
      queryValues.push(startingMonth);

      // Add the ending month
      queryValues.push(endingMonth);

      // Merge the queries
      locationsQuery = locationsQuery + " MONTH(TimestampMs) BETWEEN ? AND ?";
    }

    // If an "AND" must be added...
    if(numberOfAnds != 0)
    {
      // Merge the queries
      locationsQuery = locationsQuery + " AND";

      // Reduce the counter
      numberOfAnds--;
    }

    // If a timespan has been selected...
    if(startingTime !== null && endingTime !== null)
    {
      // Add the staring time
      queryValues.push(startingTime);

      // Add the ending time
      queryValues.push(endingTime);

      // Merge the queries
      locationsQuery = locationsQuery + " HOUR(TimestampMs) BETWEEN ? AND ?";
    }

    // If there is at least one type...
    if(typeof activitiesTypes !== 'undefined')
    {
      // Split the query argument
      var types = activitiesTypes.split(",");

      // For every type...
      for(const type of types)
      {
        
      }
    }

    // Merge the missing parentheses
    locationsQuery = locationsQuery + ")";
  }
  
  // Prepare the MySQL query
  var locationsQuery = MySQLConnection.format(locationsQuery, queryValues);

  // Get the query results
  var locationsResults = await GetQueryResultAsync(locationsQuery);

  // If there is at least one result...
  if(locationsResults.length != 0)
  {
    // Get the locations
    responseBody["locations"] = locationsResults;
  }

  // Set the response body
  responseObject.json(responseBody);
});

// The service for the login page
expressService.post("/login", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Initialize the response body
  var responseBody = 
  {
    validation : false,
    locationId : null,
    id : null
  };

  // Parse the request body
  var userInfo = requestObject.body;

  // Get the username
  var username = userInfo.username;

  // Get the hashed password
  var password = userInfo.hashedPassword;

  // Prepare the MySQL query
  var query = MySQLConnection.format("SELECT HashedPassword, Id, LocationId FROM users WHERE Username = ?", username);

  // Get the query results
  var results = await GetQueryResultAsync(query);

  // If there is at least one result...
  if(results.length != 0)
  {
    // Get the hashed password
    var hashedPassword = results[0].HashedPassword;

    // Get the locations id
    var locationId = results[0].LocationId;

    // Get the user id
    var Id = results[0].Id;

    // Check if the password is correct...
    if(hashedPassword == password)
    {
      // Set the body of the response
      responseBody["locationId"] = locationId;
      responseBody["id"] = Id;
      responseBody["validation"] = true;
    }
  }
  // Set the response body
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
    locationId : null,
    id : null
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
  var locationId = uniqueIdGeneratorModule();

  // Prepare the query
  var query = MySQLConnection.format("INSERT INTO users(LocationId, Username, HashedPassword, FirstName, LastName) VALUES (?, ?, ?, ?, ?)", [locationId, username, hashedPassword, firstName, lastName]);
  
  // Execute the query
  var result = await GetQueryResultAsync(query);

  // Set the response body
  responseBody["locationId"] = locationId;
  responseBody["id"] = result.insertId;

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

  // Get the location id query argument
  var locationId = queryArguments.locationId;

  // Prepare the query
  var query = MySQLConnection.format("SELECT UploadDate FROM locations Where LocationId = ? ORDER BY TimestampMs DESC Limit 1", locationId);

  // Execute the query
  var results = await GetQueryResultAsync(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["lastUploadDate"] = GetMySQLDatePart(results[0].UploadDate);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs FROM locations WHERE LocationId = ? ORDER BY TimestampMs ASC LIMIT 1", locationId);

  // Execute the query
  results = await GetQueryResultAsync(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["initialTimestampMS"] = GetMySQLDatePart(results[0].TimestampMs);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs FROM locations WHERE LocationId = ? ORDER BY TimestampMs DESC LIMIT 1", locationId);

  // Execute the query
  results = await GetQueryResultAsync(query);

  // If there is at least one result...
  if(results.length != 0)
    // Get the date part of the result
    responseBody["lastTimestampMS"] = GetMySQLDatePart(results[0].TimestampMs);

  // Prepare the query
  query = MySQLConnection.format("SELECT TimestampMs, InVehicle, OnBicycle, OnFoot, Running, Still, Tilting, Unknown, Walking FROM activities WHERE ActivitiesId in (SELECT ActivitiesId FROM locations WHERE LocationId = ? AND ActivitiesId IS NOT NULL AND datediff(TimestampMs, CURDATE()) > -366 ORDER BY TimestampMs ASC)", locationId);

  // Execute the query
  results = await GetQueryResultAsync(query);

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
          month : month,
          value : ecoScore
        });
    }
  }

  // Get the top 3 users
  responseBody["top3"] = await GetTop3Async(locationId);
  
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

  // Get the location id query argument
  var locationId = queryArguments.locationId;

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
      var activityId = await InsertLocationsActivityAsync(location);
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
    var locationValues = [activityId, locationId, accuracy, latitudeE7, longitudeE7, timestampMs];
    
    // Prepare the query
    var query = MySQLConnection.format("INSERT INTO locations(ActivitiesId, LocationId, Accuracy, LatitudeE7, LongitudeE7, TimestampMs, UploadDate) VALUES (?, ?, ?, ?, ?, ?, CURDATE())", locationValues);

    // Execute the query
    await GetQueryResultAsync(query);
  }

  // Set the response body
  responseObject.json({status: true});
});

// The service for the user data page
expressService.get("/user/data", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Initialize the response body
  var responseBody =
  {
    activityPercentage : [],
    hourPerActivity : [],
    dayPerActivity : [],
    locations : []
  };

  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the location id query argument
  var locationId = queryArguments.locationId;

  // Get the starting date query argument
  var startingDate = queryArguments.startingDate;

  // Get the ending date query argument
  var endingDate = queryArguments.endingDate;

  // Initialize an array that will contain the query values
  var queryValues = [locationId];

  // Declare the MySQL statement
  var locationsQuery = "SELECT LatitudeE7, LongitudeE7, ActivitiesId FROM locations WHERE LocationId = ?";

  // Declare the MySQL statement
  var activitiesQuery = MySQLConnection.format("SELECT TimestampMs, InVehicle, OnBicycle, OnFoot, Running, Still, Tilting, Unknown, Walking FROM activities WHERE ActivitiesId in (SELECT ActivitiesId FROM locations WHERE LocationId = ?");

  // If the starting date is not undefined...
  if(startingDate !== null)
  {
    // Add the new query value
    queryValues.push(startingDate);

    // Merge the queries
    locationsQuery = locationsQuery + ` AND datediff(TimestampMs, "${startingDate}") >= 0`;

    // Merge the queries
    activitiesQuery = activitiesQuery + ` AND datediff(TimestampMs, "${startingDate}") >= 0`;
  }

  // If the ending date is not undefined...
  if(endingDate !== null)
  {
    // Add the new query value
    queryValues.push(endingDate);

    // Merge the queries
    locationsQuery = locationsQuery + ` AND datediff(TimestampMs, "${endingDate}") <= 0`;

    // Merge the queries
    activitiesQuery = activitiesQuery + ` AND datediff(TimestampMs, "${endingDate}") <= 0`;
  }

  // Add the missing parentheses
  activitiesQuery = activitiesQuery + ")";

  // Prepare the query
  locationsQuery = MySQLConnection.format(locationsQuery, queryValues);

  // Execute the query
  var locationResults = await GetQueryResultAsync(locationsQuery);

  // If the result is not empty...
  if(locationResults.length != 0)
  {
    // Add the location's coordinates
    responseBody["locations"] = locationResults;

    // Prepare the query
    activitiesQuery = MySQLConnection.format(activitiesQuery, queryValues);
    
    // Execute the query
    var activitiesResults = await GetQueryResultAsync(activitiesQuery);

    // If the result is not empty...
    if(activitiesResults.length != 0)
    {
      // Get the activity percentages
      responseBody["activityPercentage"] = GetActivitiesPercentage(activitiesResults);
      
      // Get the hour per activity
      responseBody["hourPerActivity"] = GetHourPerActivity(activitiesResults);

      // Get the day per activity
      responseBody["dayPerActivity"] = GetDayPerActivity(activitiesResults);
    }
  }

  // Set the body of the response
  responseObject.json(responseBody);
});

// The service for the admin clear page
expressService.delete("/admin", async (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  //Prepare the query
  var query = MySQLConnection.format("Truncate locations");

  // Execute the query
  await GetQueryResultAsync(query);

  //Prepare the query
  query = MySQLConnection.format("Truncate activities");

  // Execute the query
  await GetQueryResultAsync(query);

  //Prepare the query
  query = MySQLConnection.format("Truncate users");

  // Execute the query
  await GetQueryResultAsync(query);

  // Set the body of the response
  responseObject.json({status: true});
});

// Start the express service
expressService.listen(port, function () 
{
  console.log(`Server is running on http://${host}:${port}`);
});
