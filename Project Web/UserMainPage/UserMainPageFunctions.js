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
            var currentMonth = currentDate.getMonth(); 

            // Get the current month eco score
            var currentMonthEcoScore = data.ecoScores[currentMonth].value;

            // Set the current month eco score
            document.getElementById("ecoScoreValueLabel").innerHTML = currentMonthEcoScore + " %";

            // Get the top 3 data
            var top3Data = data.top3;

            // Initialize the leaderboard
            LeaderboardInitialization(top3Data);

            // Get the yearly eco scores
            var yearlyEcoScores = data.ecoScores;

            // Get the current date
            var currentDate = new Date();

            // Get the current month
            var currentMonth = currentDate.getMonth();

            // Initialize an array that conntain the months
            var months = ["Ιανουάριος", "Φεβρουάριος", "Μάρτιος", "Απρίλιος", "Μάϊος", "Ιούνιος", "Ιούλιος", "Αύγουστος", "Σεπτέμβριος", "Οκτώβριος", "Νοέμβριος","Δεκέμβριος"];
            
            // Declare an array for the chart labels
            labels = [];

            // Declare an array for the chart data
            data = [];

            // For evry month...
            for(var index = 0; index < 12; index++)
            {
                if(index <= currentMonth)
                {
                    labels.push(months[index]);

                    data.push(yearlyEcoScores[index].value);
                }
                else
                {
                    labels.unshift(months[index]);

                    data.push(yearlyEcoScores[index].value);
                }
            }

            // Initialize the line chart
            LineChartSetter(labels, data);
        }
    });
}

// Initialize the leaderboard
function LeaderboardInitialization(top3Data)
{
    // Set the first leaderboard position
    document.getElementById("firstPositionValueLabel").innerHTML = "1ος: " + top3Data[0].abbreviatedFullName;

    // Set the second leaderboard position
    document.getElementById("secondPositionValueLabel").innerHTML = "2ος: " + top3Data[1].abbreviatedFullName;

    // Set the third leaderboard position
    document.getElementById("thirdPositionValueLabel").innerHTML = "3ος: " + top3Data[2].abbreviatedFullName;

    // Set the user leaderboard position
    document.getElementById("userPositionValueLabel").innerHTML = "Χρήστης: " + top3Data[3].abbreviatedFullName;
}

// Initialize the line chart
function LineChartSetter(labels, data)
{
    var chartContainer = document.getElementById('GraphContainer');
    new Chart(chartContainer, {
        type: 'line',
        data: {
            labels: labels,
            datasets: [{
                label: "% of activity per month",
                data: data,
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
