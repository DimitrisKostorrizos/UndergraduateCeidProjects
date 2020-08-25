// Get the http module
var httpModule = require('http');

// Get the url module
var urlModule = require('url');

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
