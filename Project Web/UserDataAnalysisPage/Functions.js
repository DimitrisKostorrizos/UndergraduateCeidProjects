async function JSONParser() 
{
    let file = LH.json;
    let text = await file.text();
    let JSONObject = JSON.parse(text);
    MapSetter("mapid", JSONObject);
    GraphSetter("myChart", JSONObject);
}

function MapSetter(MapId, JSONObject)
{
    let CenterCoordinates = [38.230462, 21.753150];
    var map = L.map(MapId, { drawControl: true }).setView(CenterCoordinates, 14);
    L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",{
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors'
    }).addTo(map);
    
    let MarkersList = [];
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

function GraphSetter(GraphId, JSONObject)
{
    var today = new Date();
    var mm = String(today.getMonth()).padStart(2, '0');
    var months = ["Ιανουάριος", "Φεβρουάριος", "Μάρτιος", "Απρίλιος", "Μάϊος", "Ιούνιος", "Ιούλιος", "Αύγουστος", "Σεπτέμβριος", "Οκτώβριος", "Νοέμβριος","Δεκέμβριος"];
    labels = [];
    for(let index = 0; index < 12; index++)
    {
        if(index <= mm)
        {
            labels.push(months[index]);
        }
        else
        {
            labels.unshift(months[index]);
        }
    }
    var ctx = document.getElementById('myChart').getContext('2d');
    var myChart = new Chart(ctx, {
        type: 'bar',
        data: {
            labels: labels,
            datasets: [{
                label: "% of activity per month",
                data: [33, 49.2, 55, 67, 22, 11, 45, 78, 21, 45, 67, 33],
                backgroundColor: [
                    "rgba(36, 32, 56, 0.2)"
                ],
                borderColor: [
                    "rgba(36, 32, 56, 1)"
                ],
                borderWidth: 2,
                lineTension: 0,
                pointBorderWidth: 2,
                pointBorderColor: "rgba(36, 32, 56, 1)"
            }]
        },
        options: {
            scales: {
                yAxes: [{
                    ticks: {
                        beginAtZero: true
                    }
                }]
            }
        }
    });
}