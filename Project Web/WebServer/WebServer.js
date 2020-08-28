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
MySQLConnection.connect(function(err) 
{
  if (err != null) 
    console.log("MySQL Connection Error.");
  else
    console.log("Successful MySQL Connection.");
});

// Get the querystring module
var querystringModule = require('querystring');

// Set the host name
const host = 'localhost';

// Set the web server port
const port = 8080;

// Declare the dictionary that will contain the endpoints
const endpointDictionary = 
{
  "/login" : function(username)
  {
    MySQLConnection.query("SELECT HashedPassword FROM users where Username = ?", username, function (err, result, fields) 
    {
      if (err != null) 
        throw err;
      else
        console.log(result);
    });

    // if(resultSet == password)
    //   return "good";
  },
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

  // Parse the url
  var parsedUrlObject = urlParserFunction(requestObject.url);

  // Get the selected endpoint
  var selectedEndpoint = endpointMapperFunction(parsedUrlObject);

  responseObject = endpointResponse();
};

// The url parser function
const urlParserFunction = function (url) 
{
  // Parse the url
  return urlObject = urlModule.parse(url, true);
};

// The server endpoint mapper
const endpointMapperFunction = function (urlObject)
{
  // Get the pathname
  var pathname = urlObject.pathname;

  // Get the query arguments
  var queryArguments = urlObject.query;

  var endpointFunction = endpointDictionary[pathname];

  expressService.get("/login", (requestObject, responseObject) => 
  {
    requestObject.
    MySQLConnection.query("SELECT HashedPassword FROM users where Username = ?", username, function (err, result, fields) 
    {
      if (err != null) 
        throw err;
      else
        console.log(result);
    });

    // if(resultSet == password)
    //   return "good";
  });
  endpointFunction("test");
};

// The service for the login page
expressService.get("/login", (req, res) => 
{
  username = "test";
  MySQLConnection.query("SELECT HashedPassword FROM users where Username = ?", username, function (err, result, fields) 
  {
    if (err != null) 
      throw err;
    else
      console.log(result[0].HashedPassword);
  });

  // if(resultSet == password)
  //   return "good";
});

// Create the server
var webServer = expressService.listen(port, function () 
{
  console.log(`Server is running on http://${host}:${port}`);
});
