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
    var JSONObject = JSON.parse(fileContext);

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
    MapSetter("MapContainer", JSONObject);
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
function MapSetter(MapId, JSONObject)
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


    // Intialize the draw plugin options
    var drawPluginOptions = 
    {
        position: 'topright',
        draw: {
            polyline: {
            shapeOptions: {
                color: '#f357a1',
                weight: 10
            }
            },
            polygon: false,
            circle: false,
            rectangle: false
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
    
    let MarkersList = [];

    // Draw a circle for the boundaries
    L.circle(CenterCoordinates, 
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

    var coordinatesTuples = [];

    map.on('draw:created', function (e) 
    {
        // Get the layer
        const layer = e.layer;

        // When a user finishes editing a shape we get that information here
        featureGroupLayer.addLayer(layer);

        // Get the selected geo locations
        var selectedLocations = layer.toGeoJSON();

        // Get the selected coordinates
        var selectedCoordinates = selectedLocations.geometry.coordinates;

        // If there is at least one coordinates tuple...
        if(typeof selectedCoordinates !== 'undefined')
        {
            // For every coordinates...
            for(const coordinates of selectedCoordinates)
            {
                coordinatesTuples.indexOf(coordinates);
            }
        }
    });

    // For every location...
    for(const location of JSONObject.locations)
    {
        // Get the current locations coordinates
        var coordinates = [location.latitudeE7/10000000, location.longitudeE7/10000000];

        coordinatesTuples.push(coordinates);

        // Calculate the euclidean distance
        var distance = Math.sqrt(Math.pow((CenterCoordinates[0] - coordinates[0]), 2) + Math.pow((CenterCoordinates[1] - coordinates[1]), 2));
        
        // If the distance is less than 10Km...
        if (distance <= 0.1)
        {
            // Add the marker
            marker = L.marker(coordinates).addTo(map);

            // Add the popup
            marker.bindPopup(coordinates.toString()).openPopup();

            // Add the markers
            MarkersList.push(marker);
        }
        else
        {
            JSONObject.locations.splice(JSONObject.locations.indexOf(location), 1);      
        }
    }
}