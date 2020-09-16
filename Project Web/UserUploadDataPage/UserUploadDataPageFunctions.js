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
    var map = L.map(MapId, { drawControl: true }).setView(CenterCoordinates, 14);

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
            polygon: {
            allowIntersection: false, // Restricts shapes to simple polygons
            drawError: {
                color: '#e1e100', // Color the shape will turn when intersects
                message: '<strong>Polygon draw does not allow intersections!<strong> (allowIntersection: false)' // Message that will show when intersect
            },
            shapeOptions: {
                color: '#bada55'
            }
            },
            circle: false, // Turns off this drawing tool
            rectangle: {
            shapeOptions: {
                clickable: false
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

    // drawControl = new L.Control.Draw({
    //     draw : {
    //         position : 'topright',
    //         polyline : false,
    //         rectangle : false,
    //         circle : false,
    //         polygon: false,
    //         marker: false
    //     },
    //     edit : {
    //         featureGroup: drawnItems
    //       }
    // });
    // map.addControl(drawControl);

    // map.on(L.Draw.Event.CREATED, function (e) {
    //     var layer = e.layer;
    //      drawnItems.addLayer(layer);
    //  });
    
    let MarkersList = [];
    // let FullJSONObject = JSON.parse(JSON.stringify(JSONObject));
    // let FullMarkersList = [];
    // for(i = 0; i < FullJSONObject.locations.length; i++)
    // {
    //     coordinates = [ FullJSONObject.locations[i].latitudeE7/10000000, FullJSONObject.locations[0].longitudeE7/10000000]
    //     marker = L.marker(coordinates).addTo(map);
    //     MarkersList.push(marker);
    //     marker.bindPopup(coordinates.toString()).openPopup();
    // }

    // var circle = L.circle(CenterCoordinates, {
    //     color: 'red',
    //     fillColor: '#f03',
    //     fillOpacity: 0.5,
    //     radius: 10000
    // }).addTo(map);
    marker = L.marker(CenterCoordinates).addTo(map);
    let str = "Patras Center: ".concat(CenterCoordinates.toString());
    marker.bindPopup(str).openPopup();
    for(i = 0; i < JSONObject.locations.length; i++)
    {
        let coordinates = [ JSONObject.locations[i].latitudeE7/10000000, JSONObject.locations[i].longitudeE7/10000000]
        let distance = Math.sqrt( Math.pow((CenterCoordinates[0] - coordinates[0]), 2) + Math.pow((CenterCoordinates[1] - coordinates[1]), 2) );
        if (distance <= 0.1)
        {
            marker = L.marker(coordinates).addTo(map);
            marker.bindPopup(coordinates.toString()).openPopup();
            MarkersList.push(marker);
        }
    }
}