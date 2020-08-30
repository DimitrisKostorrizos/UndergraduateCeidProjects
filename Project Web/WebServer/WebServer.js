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
const { response } = require('express');

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

// Formats the timestampMs to MySQL date
function TimestampMsToMySQLDate(timestampMs)
{
  // Get the unformatted date representation of the timestampMs
  var unformattedDate = new Date(Number(timestampMs));

  // Format the date part to MySQL date
  var formattedDatePart = unformattedDate.toJSON().slice(0, 10);

  // Return the MySQL date
  return formattedDatePart;
}

// Set the host name
const host = 'localhost';

// Set the web server port
const port = 8080;

// Declare the dictionary that will contain the endpoints
const endpointDictionary = 
{
  "/user/data" : function(arguments){},
  "/admin/dashboard" : function(){},
  "/admin/analysis" : function(arguments){},
  "/admin/clear" : function(){},
  "/admin/download" : function(arguments){},
};

// The service for the login page
expressService.get("/login", (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the username query argument
  var username = queryArguments.username;

  // Get the password query argument
  var password = queryArguments.password;

  // Execute the query
  MySQLConnection.query("SELECT HashedPassword, UserId, LocationsId FROM users where Username = ?", username, function (mySQLError, result, fields) 
  {
    // If there was a MySQL error...
    if (mySQLError != null) 
      // Throw the error
      throw mySQLError;
    else
    {
      if(result.length != 0)
      {
        // Get the hashed password form the result
        var hashedPassword = result[0].HashedPassword;

        // Get the hashed password form the result
        var locationsId = result[0].LocationsId;

        // Check if the password is correct...
        if(hashedPassword == password)
        {
          // Set the body fof the response
          responseObject.json({validation: locationsId});
        }
        else
        {
          // Set the body of the response
          responseObject.json({validation: ""});
        }
      }
      else
      {
        // Set the body of the response
        responseObject.json({validation: ""});
      }
    }
  });
});

// The service for the user info page
expressService.get("/user/info", (requestObject, responseObject) => 
{
  // Set the response status
  responseObject.status(200);

  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the user id query argument
  var locationsId = queryArguments.locationsId;

  // Declare the response body
  var responseBody = 
  {
    "lastUploadDate" : "",
    "timespan" : "",
    "ecoScore" : 0,
    "top3" : []
  };

  // Execute the query
  MySQLConnection.query("SELECT UploadDate FROM locations Where LocationId = ? Order By TimestampMs DESC Limit 1", locationsId, function (mySQLError, result, fields) 
  {
    // If there was a MySQL error...
    if (mySQLError != null) 
      // Throw the error
      throw mySQLError;
    else
    {
      if(result.length != 0)
      {
        // Get the date part
        responseBody["lastUploadDate"] = result[0].UploadDate.toJSON().slice(0, 10);
      }
    }

    var firstTimestampMs;
    var lastTimestampMs;

    // Execute the query
    MySQLConnection.query("SELECT TimestampMs FROM locations Where LocationId = ? Order By TimestampMs DESC Limit 1", locationsId, function (mySQLError, result, fields) 
    {
      // If there was a MySQL error...
      if (mySQLError != null) 
        // Throw the error
        throw mySQLError;
      else
      {
        if(result.length != 0)
        {
          // Get the date part
          lastTimestampMs = result[0].TimestampMs.toJSON().slice(0, 10);
        }
      }
      
      // Execute the query
      MySQLConnection.query("SELECT TimestampMs FROM locations Where LocationId = ? Order By TimestampMs ASC Limit 1", locationsId, function (mySQLError, result, fields) 
      {
        // If there was a MySQL error...
        if (mySQLError != null) 
          // Throw the error
          throw mySQLError;
        else
        {
          if(result.length != 0)
          {
            // Get the date part
            firstTimestampMs = result[0].TimestampMs.toJSON().slice(0, 10);
          }
        }
        // 
        responseBody["timespan"] = firstTimestampMs + " : " + lastTimestampMs;

        // Execute the query
        MySQLConnection.query("SELECT ActivitiesId FROM locations Where LocationId = ?", locationsId, function (mySQLError, result, fields) 
        {
          // If there was a MySQL error...
          if (mySQLError != null) 
            // Throw the error
            throw mySQLError;
          else
          {
            if(result.length != 0)
            {
              // Get the date part
              firstTimestampMs = result[0].TimestampMs.toJSON().slice(0, 10);
            }
          }

          responseBody["timespan"] = firstTimestampMs + " : " + lastTimestampMs;
          
          // Set the response body
          responseObject.json(responseBody);
        });
        
        // Set the response body
        responseObject.json(responseBody);
      });
    });
  });
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

// Start the express service
expressService.listen(port, function () 
{
  console.log(`Server is running on http://${host}:${port}`);
});
