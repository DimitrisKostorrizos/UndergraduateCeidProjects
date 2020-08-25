// Get the http module
var httpModule = require('http');

// Get the url module
var urlModule = require('url');

// Get the querystring module
var querystringModule = require('querystring');

// Set the localhost
const host = 'localhost';

// Set the web server port
const port = 8080;

const urlParser = function (requestObject, responseObject) 
{
  responseObject.statusCode = 200;
  urlString = urlModule.parse(requestObject.url, true);
};

// Create the server
var webServer = httpModule.createServer(urlParser);

// Get the pathname
//var pathname = urlString.pathname;

// Get the query arguments
//var queryArguments = urlString.query;

// Set the server listening port
webServer.listen(port, host, () => 
{
  console.log('Server is running on http://${host}:${port}');
});
