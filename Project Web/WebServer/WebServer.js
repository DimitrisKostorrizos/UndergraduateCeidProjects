// Get the http module
var httpModule = require('http');

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

function executeDbQuery(dbQuery, queryParameters)
{
  return new Promise(data => 
  {
    MySQLConnection.query(dbQuery, queryParameters, function (err, result, fields) 
    {
      if (err != null) 
        data(err);
      else
        data(result);
    });
  });
}

async function getQueryResult(dbQuery, queryParameters)
{
  return result = await executeDbQuery(dbQuery, queryParameters);
}


// Create the MySQL connection
var MySQLConnection = mysqlModule.createConnection({
  host: "localhost",
  user: "root",
  password: "root",
  database: "locationsdb"
});

// Try to connect to the MySQL database
MySQLConnection.connect(function(err) 
{
  if (err != null) 
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
  // Set the response code to 200
  responseObject.statusCode = 200;

  var fileData = filesystemModule.readFileSync('LH.json').toString();

  var jsonData = JSON.parse(fileData);
};

// The service for the login page
expressService.get("/login", (requestObject, responseObject) => 
{
  // Get the url object
  var urlObject = urlModule.parse(requestObject.url, true);

  // Get the query arguments
  var queryArguments = urlObject.query;

  // Get the username query argument
  var username = queryArguments.username;

  // Get the password query argument
  var password = queryArguments.password;

  // Get the query result
  var result = getQueryResult("SELECT HashedPassword FROM users where Username = ?", [username]);

  // Get the hashed password form the result
  var hashedPassword = result[0].HashedPassword;
  
  // Check if the password is correct...
  if(hashedPassword == password)
    // Set the status and the header of the response
    responseObject.status(200);
  else
    // Set the status and the header of the response
    responseObject.status(200);
});

// Create the server
var webServer = expressService.listen(port, function () 
{
  console.log(`Server is running on http://${host}:${port}`);
});
