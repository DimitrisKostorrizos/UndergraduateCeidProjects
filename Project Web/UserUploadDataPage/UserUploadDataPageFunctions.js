// Declare a global variable for the json object
var JSONObject;

// Declare an array for the coordinates
var coordinatesTuples = [];

// Initialize the GUI
function Initialization()
{
    // Hide the input
    HideElement("UploadButton");

    // Show the text box
    HideElement("ChosenFilename");

    // Show the text box
    HideElement("MapContainer");
}

// Open the file explorer
function OpenFileExplorer() 
{
    // Click the collapsed input
    document.getElementById("fileInput").click();
}

// Open the file and set the map
async function OpenFile(file)
{
    // Read the local file asynchronously
    var fileContext = await ReadFileAsync(file);

    // Parse the file context
    window.JSONObject = JSON.parse(fileContext);

    // Hide the input
    HideElement("JSONFileInput");

    // Show the text box
    ShowElement("ChosenFilename");

    // Show the text box
    ShowElement("MapContainer");

    // Show the input
    ShowElement("UploadButton");

    // Set the file name
    document.getElementById("fileNameValue").innerHTML = file.name;

    // Set the map
    MapSetter("MapContainer");
}

// Hide the element
function HideElement(elementId)
{
    // Get the element by id
    var element = document.getElementById(elementId);

    // Hide the element
    element.style.display = "none"; 
}

// Show the element
function ShowElement(elementId)
{
    // Get the element by id
    var element = document.getElementById(elementId);

    // Show the element
    element.style.display = "block";     
}

// Read the file asynchronously
async function ReadFileAsync(file)
{
    // Get the text context
    var text = await file.text();

    // Return the text
    return text;
}

// Set the map
function MapSetter(MapId)
{
    // Initialize the coordinates for patra center
    var CenterCoordinates = [38.230462, 21.753150];

    // Initialize the map layer
    var map = L.map(MapId).setView(CenterCoordinates, 12);

    // Initialize a map layer
    var mapLayer = L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",{
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors'
    });

    // Add the map layer to the map
    map.addLayer(mapLayer);

    // Initialize a group for the editable layers
    var featureGroupLayer = new L.FeatureGroup();

    // Add the feature layer to the map
    map.addLayer(featureGroupLayer);

    // Initialize the draw plugin options
    var drawPluginOptions = 
    {
        position: 'topright',
        draw: {
            polyline: false,
            polygon: false,
            circle: false,
            rectangle: {
                shapeOptions: {
                    color: '#f357a1',
                    weight: 10
                }
                }
        },
        edit: {
            featureGroup: featureGroupLayer,
            remove: false
        }
    };

    // Initialize the draw control
    var drawControl = new L.Control.Draw(drawPluginOptions);

    // Add the draw control to the map
    map.addControl(drawControl);

    // Draw a circle for the boundaries
    var circle = L.circle(CenterCoordinates, 
        {
        color: 'blue',
        fillColor: '#02C39A',
        fillOpacity: 0.3,
        radius: 10000
    }).addTo(map);

    // Set a marker for the patras center
    marker = L.marker(CenterCoordinates).addTo(map);
    var str = "Patras Center: ".concat(CenterCoordinates.toString());
    marker.bindPopup(str).openPopup();

    // Get the circle bounds
    var circleBounds = circle.getBounds();

    // For every location...
    for(const location of JSONObject.locations)
    {
        // Get the current locations coordinates
        var coordinates = [location.latitudeE7/10000000, location.longitudeE7/10000000];

        if(circleBounds.contains(coordinates))
            // Add it to the valid coordinates
            coordinatesTuples.push(coordinates);
        else
            // Delete the current location
            JSONObject.locations.splice(JSONObject.locations.indexOf(location), 1);
    }

    // Set the event when a shape is created
    map.on('draw:created', function (e) 
    {
        // Get the layer
        var layer = e.layer;

        // Get the rectangle bounds
        var rectangleBounds = L.latLngBounds(layer.getLatLngs());

        // For every tuple of coordinates...
        for(var index = 0; index < coordinatesTuples.length; index++)
        {
            // If the coordinates are contained within the bound...
            if(rectangleBounds.contains(coordinatesTuples[index]))
            {
                // Remove the coordinates entry
                JSONObject.locations.splice(index, 1);

                // Remove the coordinates entry
                coordinatesTuples.splice(index, 1);
            }
        }
    });
}

// Upload the file
function Upload()
{
    // If the json is not empty...
    if(JSONObject.locations.length == 0)
        alert("No locations to upload.");
    else
    {
        // Set the url
        var url = new URL("http://localhost:8080/user/upload");
    
        // Get the user's location id
        var locationId = "704d432a-142c-469e-b7c3-3b1b4e57ba10";
        //var locationId = localStorage.getItem("locationId");
        
        // Set the url query parameters
        url.searchParams.set('locationId', locationId);
    
        // Send the request
        $.ajax({
            url: url,
            data: JSON.stringify(JSONObject),
            headers: 
            {
                "Content-Type": "application/json"
            },
            type: 'Post',
            success: function(data)
            {
                // If the upload was successful...
                if(data.status)
                    alert("Upload was cleared successfully.");
                else
                    alert("Upload has failed.");
            }
        });
    }
}