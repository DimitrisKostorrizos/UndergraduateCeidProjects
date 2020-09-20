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
            // Get the locations
            var locations = data.locations;

            // If there is at least one location...
            if(locations.length != 0)
            {
                // Declare the array that will conatin the coordinates
                var locationCoordinates = [];

                // For every location...
                for(const location of locations)
                {
                    locationCoordinates.push([location.LatitudeE7/10000000, location.LongitudeE7/10000000, 10]);
                }

                // Set the heat map
                HeatMapSetter(locationCoordinates);
            }
        }
    });    
}

function Export()
{
    // Set the url
    var url = new URL("http://localhost:8080/admin/export");

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
            // Get the locations
            var locations = data.locations;

            // If there is at least one location...
            if(locations.length != 0)
            {
                var radioInputElement = document.getElementsByName("FileExtensionInput");

                var exportFileExtension;

                for (var index = 0; index < radioInputElement.length; index++) 
                {
                    if (radioInputElement[index].checked) 
                    {
                      exportFileExtension = radioInputElement[index].value;

                      break;
                    }
                }

                if(exportFileExtension == "CSV")
                {
                    // Get the JSON data
                    var stringData = JsonToCsv(locations);

                    // Create the file containing
                    var blob = new Blob([stringData], {type: 'application/json'});
                    
                    // Download the file
                    SaveLocalFile(blob, 'data.csv');
                }
                else if(exportFileExtension == "XML")
                {
                    // Get the JSON data
                    var stringData = JSONtoXML(locations);

                    // Create the file containing
                    var blob = new Blob([stringData], {type: 'application/json'});
                    
                    // Download the file
                    SaveLocalFile(blob, 'data.xml');
                }
                else if(exportFileExtension == "JSON")
                {
                    // Get the JSON data
                    var stringData = JSON.stringify(locations);

                    // Create the file containing
                    var blob = new Blob([stringData], {type: 'application/json'});
                    
                    // Download the file
                    SaveLocalFile(blob, 'data.json');
                }
            }
        }
    });
}

// Initialize the heat map
function HeatMapSetter(data)
{
    // Initialize the map
    var map = new L.Map("HeatmapContainer", 
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

function JsonToCsv(jsonData)
{
    // Get the Json items
  var JsonItems = Object.entries(jsonData);

  // Set the replacer for the null values
  var nullValueReplacer = (key, value) => value === null ? '' : value;

  // Get the csv headers
  var header = Object.keys(JsonItems[0]);

  // Get the csv context
  var csvContext = JsonItems.map(row => header.map(fieldName => JSON.stringify(row[fieldName], nullValueReplacer)).join(','))
  
  // Add the headers at the first position
  csvContext.unshift(header.join(','));

  // Add a new line character at the end
  csvContext = csvContext.join('\r\n');

  // Return the csvContext
  return csvContext;
}

function JSONtoXML(obj) 
{
    var xml = '';

    for (var prop in obj) 
    {
      xml += obj[prop] instanceof Array ? '' : "<" + prop + ">";
      if (obj[prop] instanceof Array) 
      {
        for (var array in obj[prop]) 
        {
          xml += "<" + prop + ">";
          xml += JSONtoXML(new Object(obj[prop][array]));
          xml += "</" + prop + ">";
        }
      } 
      else if (typeof obj[prop] == "object") 
      {
        xml += JSONtoXML(new Object(obj[prop]));
      } 
      else 
      {
        xml += obj[prop];
      }
      xml += obj[prop] instanceof Array ? '' : "</" + prop + ">";
    }

    xml = xml.replace(/<\/?[0-9]{1,}>/g, '');

    return xml;
}

function SaveLocalFile(blob, filename)
{
    var url = URL.createObjectURL(blob);
    var link = document.createElement('a');
    link.setAttribute('href', url);
    link.setAttribute('download', filename);
    var event = document.createEvent('MouseEvents');
    event.initMouseEvent('click', true, true, window, 1, 0, 0, 0, 0, false, false, false, false, 0, null);
    link.dispatchEvent(event);
}