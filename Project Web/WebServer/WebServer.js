// Get the url module
var urlModule = require('url');

// Get the file system module
var filesystemModule = require('fs');

// Get the MySQL driver module
var mysqlModule = require('mysql');

// Get the express module
var expressModule = require('express');

// Initialize the express service
var expressService = expressModule();

// Get the querystring module
var querystringModule = require('querystring');

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

// Set the host name
const host = 'localhost';

// Set the web server port
const port = 8080;

// Declare the dictionary that will contain the endpoints
const endpointDictionary = 
{
  "/user/info" : function(){},
  "/user/data" : function(arguments){},
  "/user/upload" : function(){},
  "/admin/dashboard" : function(){},
  "/admin/analysis" : function(arguments){},
  "/admin/clear" : function(){},
  "/admin/download" : function(arguments){},
};

var code = uniqueIdGeneratorModule();

// The server listening function
const webServerListeningFunction = function (requestObject, responseObject)
{
  var fileData = filesystemModule.readFileSync('LH.json').toString();

  var jsonData = JSON.parse(fileData);
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
  MySQLConnection.query("SELECT HashedPassword FROM users where Username = ?", username, function (mySQLError, result, fields) 
  {
    // If there was a MySQL error...
    if (mySQLError != null) 
      // Throw the error
      throw mySQLError;
    else
    {
      // Get the hashed password form the result
      var hashedPassword = result[0].HashedPassword;

      // Check if the password is correct...
      if(hashedPassword == password)
      {
        // Set the body fof the response
        responseObject.json({validation: "Success"});
      }
      else
        // Set the body of the response
        responseObject.json({validation: "Failure"});
    }
  });
});

// The service for the login page
expressService.get("/user/info", (requestObject, responseObject) => 
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
  MySQLConnection.query("SELECT HashedPassword FROM users where Username = ?", username, function (mySQLError, result, fields) 
  {
    // If there was a MySQL error...
    if (mySQLError != null) 
      // Throw the error
      throw mySQLError;
    else
    {
      // Get the hashed password form the result
      var hashedPassword = result[0].HashedPassword;

      // Check if the password is correct...
      if(hashedPassword == password)
      {
        // Set the body fof the response
        responseObject.json({validation: "Success"});
      }
      else
        // Set the body of the response
        responseObject.json({validation: "Failure"});
    }
  });
});

// Create the server
var webServer = expressService.listen(port, function () 
{
  console.log(`Server is running on http://${host}:${port}`);
});
