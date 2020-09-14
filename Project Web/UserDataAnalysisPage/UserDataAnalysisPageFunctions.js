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

function Search()
{
    // Set the url
    var url = new URL("http://localhost:8080/user/data");

    // Get the user's location id
    var locationId = "704d432a-142c-469e-b7c3-3b1b4e57ba10";
    //var locationId = localStorage.getItem("locationId");
    
    // Set the url query parameters
    url.searchParams.set('locationId', locationId);

    // Get the starting date value
    var startingDate = document.getElementById('startingMonthInput').value;

    // If the value is not empty...
    if(startingDate !== "")
    {
        // Add the missing day part
        startingDate = startingDate + "-01";

        // Add the starting date to the url
        url.searchParams.set('startingDate', startingDate);
    }

    // Get the ending date value
    var endingDate = document.getElementById('endingMonthInput').value;

    // If the value is not empty...
    if(endingDate !== "")
    {
        // Add the missing day part
        endingDate = endingDate + "-01";

        // Add the starting date to the url
        url.searchParams.set('endingDate', endingDate);
    }

    // Send the request
    $.ajax({
        url: url,
        headers: 
        {
            "Content-Type": "application/json"
        },
        type: 'Get',
        success: function(data)
        {
            // Get the activities percentage
            var activityPercentage = data.activityPercentage;

            // If activities percentage is not empty...
            if(activityPercentage.length != 0)
            {
                // Set the value
                document.getElementById("activityInVehicleValueLabel").innerHTML = activityPercentage.InVehicle + " %";
            }
            else
            {
                // Set the value
                document.getElementById("activityInVehicleValueLabel").innerHTML = "";
            }

            // Initialize the line chart
            LineChartSetter(labels, data);
        }
    });
};

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