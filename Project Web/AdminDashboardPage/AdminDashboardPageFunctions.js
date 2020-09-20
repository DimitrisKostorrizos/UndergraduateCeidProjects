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

            LineChartSetter("UserDataChartContainer", DatasetSetter(activitiesPerUserPercentage), "Activities Per User");

            // Get the activities per month percentage
            var activitiesPerMonthPercentage = data.activitiesPerMonthPercentage;

            LineChartSetter("MonthDataChartContainer", DatasetSetter(activitiesPerMonthPercentage), "Activities Per Month");

            // Get the activities per weekday percentage
            var activitiesPerWeekDayPercentage = data.activitiesPerWeekDayPercentage;

            LineChartSetter("WeekDayDataChartContainer", DatasetSetter(activitiesPerWeekDayPercentage), "Activities Per Weekday");

            // Get the activities per hour percentage
            var activitiesPerHourPercentage = data.activitiesPerHourPercentage;

            LineChartSetter("HourDataChartContainer", DatasetSetter(activitiesPerHourPercentage), "Activities Per Hour");

            // Get the activities per year percentage
            var activitiesPerYearPercentage = data.activitiesPerYearPercentage;
            
            LineChartSetter("YearDataChartContainer", DatasetSetter(activitiesPerYearPercentage), "Activities Per Year");
        }
    }); 
}

function DatasetSetter(data)
{
    var labels = [];

    var activityData = 
    [
        inVehicleData = [],
        onBicycleData = [],
        onFootData = [],
        runningData = [],
        stillData = [],
        tiltingData = [],
        unknownData = [],
        walkingData = []
    ];

    
    for(const entry of data)
    {
        var entryValues = Object.values(entry);

        labels.push(entryValues[0]);

        if(entryValues[1] != null)
        {
            var values = Object.values(entryValues[1]);

            for(var index = 0; index < values.length; index++)
            {
                activityData[index].push(Math.round(values[index]));
            }
        }
        else
        {
            for(var index = 0; index < 8; index++)
            {
                activityData[index].push(0);
            }
        }
    }

    var dataset = 
    {
        labels: labels,
        datasets: [
        {
            label: "% of InVehicle activity type",
            data: activityData[0],
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
        },
        {
            label: "% of OnBicycle activity type",
            data: activityData[1],
            backgroundColor: [
                "rgba(252, 186, 3, 0.2)"
            ],
            borderColor: [
                "rgba(252, 186, 3, 1)"
            ],
            borderWidth: 2,
            lineTension: 0,
            pointBorderWidth: 2,
            pointBorderColor: "rgba(252, 186, 3, 1)"
        },
        {
            label: "% of OnFoot activity type",
            data: activityData[2],
            backgroundColor: [
                "rgba(32, 252, 3, 0.2)"
            ],
            borderColor: [
                "rgba(32, 252, 3, 1)"
            ],
            borderWidth: 2,
            lineTension: 0,
            pointBorderWidth: 2,
            pointBorderColor: "rgba(32, 252, 3, 1)"
        },
        {
            label: "% of Running activity type",
            data: activityData[3],
            backgroundColor: [
                "rgba(3, 20, 252, 0.2)"
            ],
            borderColor: [
                "rgba(3, 20, 252, 1)"
            ],
            borderWidth: 2,
            lineTension: 0,
            pointBorderWidth: 2,
            pointBorderColor: "rgba(3, 20, 252, 1)"
        },
        {
            label: "% of Still activity type",
            data: activityData[4],
            backgroundColor: [
                "rgba(252, 3, 206, 0.2)"
            ],
            borderColor: [
                "rgba(252, 3, 206, 1)"
            ],
            borderWidth: 2,
            lineTension: 0,
            pointBorderWidth: 2,
            pointBorderColor: "rgba(252, 3, 206, 1)"
        },
        {
            label: "% of Tilting activity type",
            data: activityData[5],
            backgroundColor: [
                "rgba(252, 20, 3, 0.2)"
            ],
            borderColor: [
                "rgba(252, 20, 3, 1)"
            ],
            borderWidth: 2,
            lineTension: 0,
            pointBorderWidth: 2,
            pointBorderColor: "rgba(252, 20, 3, 1)"
        },
        {
            label: "% of Unknown activity type",
            data: activityData[6],
            backgroundColor: [
                "rgba(123, 3, 252, 0.2)"
            ],
            borderColor: [
                "rgba(123, 3, 252, 1)"
            ],
            borderWidth: 2,
            lineTension: 0,
            pointBorderWidth: 2,
            pointBorderColor: "rgba(123, 3, 252, 1)"
        },
        {
            label: "% of Walking activity type",
            data: activityData[7],
            backgroundColor: [
                "rgba(3, 252, 211, 0.2)"
            ],
            borderColor: [
                "rgba(3, 252, 211, 1)"
            ],
            borderWidth: 2,
            lineTension: 0,
            pointBorderWidth: 2,
            pointBorderColor: "rgba(3, 252, 211, 1)"
        },
        ]
    };

    return dataset;
}

// Initialize the line chart
function LineChartSetter(elementId, dataset, chartTitle)
{
    var chartContainer = document.getElementById(elementId);
    new Chart(chartContainer, {
        type: 'line',
        data: dataset,
        options: {
            title : 
            {
                display : true,
                text : chartTitle
            },
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

function LoadDashboardPage()
{
    // Get the user's status
    var status = localStorage.getItem("status");

    // If the user has admin status...
    if(status == 1)
        // Redirect to the admin dashboard page
        window.location.href='../AdminDashboardPage/AdminDashboardPage.html';
    else
        // Redirect to the user main page
        window.location.href='../LoginFormPage/LoginFormPage.html';
}

function LoadShowDataPage()
{
    // Get the user's status
    var status = localStorage.getItem("status");

    // If the user has admin status...
    if(status == 1)
        // Redirect to the show data page
        window.location.href='../AdminShowDataPage/AdminShowDataPage.html';
    else
        // Redirect to the user main page
        window.location.href='../LoginFormPage/LoginFormPage.html';
}

function LoadClearDatabasePage()
{
    // Get the user's status
    var status = localStorage.getItem("status");

    // If the user has admin status...
    if(status == 1)
        // Redirect to the admin clear database page
        window.location.href='../AdminClearDatabasePage/AdminClearDatabasePage.html';
    else
        // Redirect to the user main page
        window.location.href='../LoginFormPage/LoginFormPage.html';
}