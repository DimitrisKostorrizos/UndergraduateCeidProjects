// Get the http module
var httpModule = require('http');

// Get the url module
var urlModule = require('url');

// Get the file system module
var filesystemModule = require('fs');

// Get the MySQL driver module
var mysqlModule = require('mysql');

// Create the MySQL connection
var MySQLConnection = mysqlModule.createConnection({
  host: "localhost",
  user: "root",
  password: "root"
});

// Try to connect to the MySQL database
MySQLConnection.connect(function(err) 
{
  if (err != null) 
    console.log("MySQL Connection Error.");
  else
    console.log("Successful MySQL Connection,");
});

// Get the querystring module
var querystringModule = require('querystring');

// Set the host name
const host = 'localhost';

// Set the web server port
const port = 8080;

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
};

// The server endpoint response
const endpointResponse = function ()
{

};

// Create the server
var webServer = httpModule.createServer(webServerListeningFunction);

// Set the server listening port
webServer.listen(port, host, () => 
{
  console.log(`Server is running on http://${host}:${port}`);
});
