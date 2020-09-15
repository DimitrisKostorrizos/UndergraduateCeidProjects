function OpenFileExplorer() 
{
    // Click the collapsed input
    document.getElementById("fileInput").click();
}

async function OpenFile(file)
{
    // Read the loacl file asynchronously
    var fileContext = await ReadFileAsync(file);

    // Parse the file context
    var JSONObject = JSON.parse(fileContext);

    MapSetter(MapId, JSONObject);
}

// Read the file asynchronously
async function ReadFileAsync(file)
{
    // Get the text context
    var text = await file.text();

    // Return the text
    return text;
}

function MapSetter(MapId, JSONObject)
{
    let CenterCoordinates = [38.230462, 21.753150];
    var map = L.map(MapId, { drawControl: true }).setView(CenterCoordinates, 14);
    L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",{
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors'
    }).addTo(map);

    var drawnItems = new L.FeatureGroup();
    map.addLayer(drawnItems);

    drawControl = new L.Control.Draw({
        draw : {
            position : 'topright',
            polyline : false,
            rectangle : false,
            circle : false,
            polygon: false,
            marker: false
        },
        edit : {
            featureGroup: drawnItems
          }
    });
    map.addControl(drawControl);

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