function Initialization()
{
    // Set the url
    var url = new URL("http://localhost:8080/user/info");

    // Get the user's location id
    var locationId = "704d432a-142c-469e-b7c3-3b1b4e57ba10";
    //var locationId = localStorage.getItem("locationId");

    // Set the url query parameters
    url.searchParams.set('locationId', locationId);

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
            // Get the last upload date
            var lastUploadDate = data.lastUploadDate;

            // If the last upload date is not null...
            if(lastUploadDate != null)
                // Set the last upload date
                document.getElementById("lastUploadValueLabel").innerHTML = lastUploadDate;
            else
                // Set the last upload date
                document.getElementById("lastUploadValueLabel").innerHTML = "";

            // Get the period timespan
            var periodTimespan = data.initialTimestampMS + " - " + data.lastTimestampMS;

            // If period timespan is not null...
            if(periodTimespan != null)
                // Set the last upload date
                document.getElementById("periodTimespanValueLabel").innerHTML = periodTimespan;
            else
                // Set the last upload date
                document.getElementById("periodTimespanValueLabel").innerHTML = "";
            
            // Get the current date
            var currentDate = new Date();

            // Get the current month part
            var currentMonth = currentDate.getMonth();//String(currentDate.getMonth()).padStart(2, '0'); 

            // Get the current month eco score
            var currentMonthEcoScore = data.ecoScores[currentMonth].value;

            // Set the current month eco score
            document.getElementById("ecoScoreValueLabel").innerHTML = currentMonthEcoScore + " %";
        }
    });
}

function GraphSetter()
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
        type: 'line',
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

function LeaderboardSetter(firstid,secondid,thirdid,userid,userposition)
{
    document.getElementById(firstid).innerHTML = "first";
    document.getElementById(secondid).innerHTML = "Second";
    document.getElementById(thirdid).innerHTML = "Third";
    document.getElementById(userid).innerHTML = "User";
    document.getElementById(userposition).innerHTML = "56";
}