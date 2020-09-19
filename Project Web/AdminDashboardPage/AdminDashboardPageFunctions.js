function Initialization()
{
    // Set the url
    var url = new URL("http://localhost:8080/admin/dashboard");

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
            var activityPercentage = data.activitiesPercentage;

            // If activities percentage is not empty...
            if(activityPercentage.length != 0)
            {
                // Set the value
                document.getElementById("activityInVehicleValueLabel").innerHTML = Math.round(activityPercentage.InVehicle) + " %";

                // Set the value
                document.getElementById("activityOnBicycleValueLabel").innerHTML = Math.round(activityPercentage.OnBicycle) + " %";

                // Set the value
                document.getElementById("activityOnFootValueLabel").innerHTML = Math.round(activityPercentage.OnFoot) + " %";

                // Set the value
                document.getElementById("activityRunningValueLabel").innerHTML = Math.round(activityPercentage.Running) + " %";

                // Set the value
                document.getElementById("activityStillValueLabel").innerHTML = Math.round(activityPercentage.Still) + " %";

                // Set the value
                document.getElementById("activityTiltingValueLabel").innerHTML = Math.round(activityPercentage.Tilting) + " %";

                // Set the value
                document.getElementById("activityUnknownValueLabel").innerHTML = Math.round(activityPercentage.Unknown) + " %";

                // Set the value
                document.getElementById("activityWalkingValueLabel").innerHTML = Math.round(activityPercentage.Unknown) + " %";
            }
            else
            {
                // Set the value
                document.getElementById("activityInVehicleValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("activityOnBicycleValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("activityOnFootValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("activityRunningValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("activityStillValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("activityTiltingValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("activityUnknownValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("activityWalkingValueLabel").innerHTML = "";
            }

            // Get the activities per user percentage
            var activitiesPerUserPercentage = data.activitiesPerUserPercentage;

            // Get the activities per month percentage
            var activitiesPerMonthPercentage = data.activitiesPerMonthPercentage;

            // Get the activities per weekday percentage
            var activitiesPerWeekDayPercentage = data.activitiesPerWeekDayPercentage;

            // Get the activities per hour percentage
            var activitiesPerHourPercentage = data.activitiesPerHourPercentage;

            // Get the activities per year percentage
            var activitiesPerYearPercentage = data.activitiesPerYearPercentage;
        }
    }); 
}

// Initialize the line chart
function LineChartSetter(elementId, labels, data)
{
    var chartContainer = document.getElementById(elementId);
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