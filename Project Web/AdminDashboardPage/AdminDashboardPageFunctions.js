function Initialization()
{
    // Set the url
    var url = new URL("http://localhost:8080/admin/dashboard");

    var body = document.getElementsByTagName('UsersChartsContainer')[0],
    newdiv = document.createElement('div');   //create a div
    newdiv.id = 'newid';                      //add an id
    body.appendChild(newdiv);                 //append to the doc.body
    body.insertBefore(newdiv,body.firstChild) //OR insert it

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
            {}
        }
    }); 
}