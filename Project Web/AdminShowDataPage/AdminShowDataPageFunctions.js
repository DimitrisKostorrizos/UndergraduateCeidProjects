function Search()
{
    // Set the url
    var url = new URL("http://localhost:8080/admin/analysis");

    // Get the staring month value
    var startingMonthValue = document.getElementById("startingMonthInput").value;

    // Get the ending month value
    var endingMonthValue = document.getElementById("endingMonthInput").value;

    // Get the starting day value
    var startingDayValue = document.getElementById("startingDayInput").value;

    // Get the ending day value
    var endingDayValue = document.getElementById("endingDayInput").value;

    // Get the staring hour value
    var staringHourValue = document.getElementById("startingHourInput").value;

    // Get the ending hour value
    var endingHourValue = document.getElementById("endingHourInput").value;

    // If the year-month in not empty...
    if(startingMonthValue !== '' || endingMonthValue !== '')
    {
        // Initialize the staring year
        var startingYear = startingMonthValue.slice(0, 4);

        // Initialize the staring month
        var startingMonth = startingMonthValue.slice(5, 7);

        // Initialize the ending year
        var endingYear = endingMonthValue.slice(0, 4);

        // Initialize the ending month
        var endingMonth = endingMonthValue.slice(5, 7);

        // If the starting month is empty...
        if(startingMonthValue === '')
        {
            // Set the staring year
            startingYear = endingYear;

            // Set the staring month
            startingMonth = endingMonth;
        }
        
        // If the ending month is empty...
        if(endingMonthValue === '')
        {
            // Set the ending year
            endingYear = startingYear;

            // Set the ending month
            endingMonth = startingMonth;
        }

        // Add the starting year to the url
        url.searchParams.set('startingYear', startingYear);

        // Add the ending year to the url
        url.searchParams.set('endingYear', endingYear);

        // Add the starting month to the url
        url.searchParams.set('startingMonth', startingMonth);

        // Add the ending month to the url
        url.searchParams.set('endingMonth', endingMonth);
    }

    // If the day in not empty...
    if(startingDayValue !== '' || endingDayValue !== '')
    {
        // Initialize the staring day
        var startingDay = startingDayValue;

        // Initialize the ending day
        var endingDay = endingDayValue;

        // If the starting day is empty...
        if(startingDayValue === '')
        {
            // Set the starting day
            startingDay = endingDay;
        }

        // If the ending day is empty...
        if(endingDayValue === '')
        {
            // Set the ending day
            endingDay = startingDay;
        }

        // Add the starting day to the url
        url.searchParams.set('startingDay', startingDay);

        // Add the ending day to the url
        url.searchParams.set('endingDay', endingDay);
    }

    // If the hour in not empty...
    if(staringHourValue !== '' || endingHourValue !== '')
    {
        // Initialize the staring time
        var staringHour = staringHourValue.slice(0, 2);

        // Initialize the ending time
        var endingHour = endingHourValue.slice(0, 2);

        // If the starting hour is empty...
        if(staringHourValue === '')
        {
            // Set the starting day
            staringHour = endingHour;
        }

        // If the ending hour is empty...
        if(endingHourValue === '')
        {
            // Set the ending day
            endingHour = staringHour;
        }

        // Add the starting hour to the url
        url.searchParams.set('staringHour', staringHour);

        // Add the ending hour to the url
        url.searchParams.set('endingHour', endingHour);
    }

    // Declare an array that will contain the selected activity types
    var selectedActivityTypes = [];

    // If the InVehicle checkbox is checked...
    if(document.getElementById("inVehicleCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("InVehicle");
        
    // If the OnBicycle checkbox is checked...
    if(document.getElementById("onBicycleCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("OnBicycle");
    
    // If the OnFoot checkbox is checked...
    if(document.getElementById("onFootCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("onFoot");

    // If the Running checkbox is checked...
    if(document.getElementById("runningCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("Running");

    // If the Still checkbox is checked...
    if(document.getElementById("stillCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("Still");

    // If the tilting checkbox is checked...
    if(document.getElementById("tiltingCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("tilting");

    // If the unknown checkbox is checked...
    if(document.getElementById("unknownCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("unknown");

    // If the walking checkbox is checked...
    if(document.getElementById("walkingCheckbox").checked)
        // Add the activity type
        selectedActivityTypes.push("walking");

    // If there was selected at least one activity...
    if(selectedActivityTypes.length != 0)
    {
        // Join the activity type
        var activitiesTypes = selectedActivityTypes.join(",");

        // Add the starting hour to the url
        url.searchParams.set('activityTypes', activitiesTypes);
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
        }
    });    
}

function Export()
{

}

function HeatmapSetter(heatmapId)
{

}