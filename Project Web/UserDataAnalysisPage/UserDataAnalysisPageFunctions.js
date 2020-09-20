function Search()
{
    // Set the url
    var url = new URL("http://localhost:8080/user/data");

    // Get the user's location id
    var locationId = localStorage.getItem("locationId");
    
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

                // Set the value
                document.getElementById("activityOnBicycleValueLabel").innerHTML = activityPercentage.OnBicycle + " %";

                // Set the value
                document.getElementById("activityOnFootValueLabel").innerHTML = activityPercentage.OnFoot + " %";

                // Set the value
                document.getElementById("activityRunningValueLabel").innerHTML = activityPercentage.Running + " %";

                // Set the value
                document.getElementById("activityStillValueLabel").innerHTML = activityPercentage.Still + " %";

                // Set the value
                document.getElementById("activityTiltingValueLabel").innerHTML = activityPercentage.Tilting + " %";

                // Set the value
                document.getElementById("activityUnknownValueLabel").innerHTML = activityPercentage.Unknown + " %";

                // Set the value
                document.getElementById("activityWalkingValueLabel").innerHTML = activityPercentage.Unknown + " %";
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

            // Get the day per activity percentage
            var dayPerActivityPercentage = data.dayPerActivity;

            // If the day per activity percentage is not empty...
            if(dayPerActivityPercentage.length != 0)
            {
                // Declare the months names
                var dayNames = ["Κυριακή", "Δευτέρα", "Τρίτη", "Τετάρτη", "Πέμπτη", "Παρασκευή", "Σάββατο"];
                
                // Set the value
                document.getElementById("dayPerActivityInVehicleValueLabel").innerHTML = dayNames[dayPerActivityPercentage.InVehicle];

                // Set the value
                document.getElementById("dayPerActivityOnBicycleValueLabel").innerHTML = dayNames[dayPerActivityPercentage.OnBicycle];

                // Set the value
                document.getElementById("dayPerActivityOnFootValueLabel").innerHTML = dayNames[dayPerActivityPercentage.OnFoot];

                // Set the value
                document.getElementById("dayPerActivityRunningValueLabel").innerHTML = dayNames[dayPerActivityPercentage.Running];

                // Set the value
                document.getElementById("dayPerActivityStillValueLabel").innerHTML = dayNames[dayPerActivityPercentage.Still];

                // Set the value
                document.getElementById("dayPerActivityTiltingValueLabel").innerHTML = dayNames[dayPerActivityPercentage.Tilting];

                // Set the value
                document.getElementById("dayPerActivityUnknownValueLabel").innerHTML = dayNames[dayPerActivityPercentage.Unknown];

                // Set the value
                document.getElementById("dayPerActivityWalkingValueLabel").innerHTML = dayNames[dayPerActivityPercentage.Walking];
            }
            else
            {
                // Set the value
                document.getElementById("dayPerActivityInVehicleValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("dayPerActivityOnBicycleValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("dayPerActivityOnFootValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("dayPerActivityRunningValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("dayPerActivityStillValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("dayPerActivityTiltingValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("dayPerActivityUnknownValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("dayPerActivityWalkingValueLabel").innerHTML = "";
            }

            // Get the hour per activity percentage
            var hourPerActivityPercentage = data.hourPerActivity;

            // If the hour per activity percentage is not empty...
            if(hourPerActivityPercentage.length != 0)
            {
                // Set the value
                document.getElementById("hourPerActivityInVehicleValueLabel").innerHTML = hourPerActivityPercentage.InVehicle + ":00";

                // Set the value
                document.getElementById("hourPerActivityOnBicycleValueLabel").innerHTML = hourPerActivityPercentage.OnBicycle + ":00";

                // Set the value
                document.getElementById("hourPerActivityOnFootValueLabel").innerHTML = hourPerActivityPercentage.OnFoot + ":00";

                // Set the value
                document.getElementById("hourPerActivityRunningValueLabel").innerHTML = hourPerActivityPercentage.Running + ":00";

                // Set the value
                document.getElementById("hourPerActivityStillValueLabel").innerHTML = hourPerActivityPercentage.Still + ":00";

                // Set the value
                document.getElementById("hourPerActivityTiltingValueLabel").innerHTML = hourPerActivityPercentage.Tilting + ":00";

                // Set the value
                document.getElementById("hourPerActivityUnknownValueLabel").innerHTML = hourPerActivityPercentage.Unknown + ":00";

                // Set the value
                document.getElementById("hourPerActivityWalkingValueLabel").innerHTML = hourPerActivityPercentage.Walking + ":00";
            }
            else
            {
                // Set the value
                document.getElementById("hourPerActivityInVehicleValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("hourPerActivityOnBicycleValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("hourPerActivityOnFootValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("hourPerActivityRunningValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("hourPerActivityStillValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("hourPerActivityTiltingValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("hourPerActivityUnknownValueLabel").innerHTML = "";

                // Set the value
                document.getElementById("hourPerActivityWalkingValueLabel").innerHTML = "";
            }

            // Get the locations
            var locations = data.locations;

            // If there is at least one location...
            if(locations.length != 0)
            {
                // Declare the array that will contain the coordinates
                var locationCoordinates = [];

                // For every location...
                for(const location of locations)
                {
                    locationCoordinates.push([location.LatitudeE7/10000000, location.LongitudeE7/10000000, 10]);
                }
    
                // Initialize the heat map
                HeatMapSetter(locationCoordinates);
            }
        }
    });
}

// Initialize the heat map
function HeatMapSetter(data)
{
    // Initialize the map
    var map = new L.Map("heatMap", 
    {
        center: new L.LatLng(38.230462, 21.753150),
        zoom: 14
    });

    // Initialize the map layer
    var mapLayer = L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",{
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors'
    });

    // Add the map layer to the map
    map.addLayer(mapLayer);

    // Initialize the heat map layer
    var heatmapLayer = L.heatLayer(data);

    // Add the heat map layer to the map
    map.addLayer(heatmapLayer);
}

function LoadMainPage()
{
    // Get the user's status
    var status = localStorage.getItem("status");

    // If the user has user status...
    if(status == 0)
        // Redirect to the user main page
        window.location.href='../UserMainPage/UserMainPage.html';
    else
        // Redirect to the user main page
        window.location.href='../LoginFormPage/LoginFormPage.html';
}

function LoadDataAnalysisPage()
{
    // Get the user's status
    var status = localStorage.getItem("status");

    // If the user has user status...
    if(status == 0)
        // Redirect to the user data analysis page
        window.location.href='../UserDataAnalysisPage/UserDataAnalysisPage.html';
    else
        // Redirect to the user main page
        window.location.href='../LoginFormPage/LoginFormPage.html';
}

function LoadUploadDataPage()
{
    // Get the user's status
    var status = localStorage.getItem("status");

    // If the user has user status...
    if(status == 0)
        // Redirect to the user upload data page
        window.location.href='../UserUploadDataPage/UserUploadDataPage.html';
    else
        // Redirect to the user main page
        window.location.href='../LoginFormPage/LoginFormPage.html';
}