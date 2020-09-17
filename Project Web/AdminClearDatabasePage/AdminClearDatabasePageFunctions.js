function ClearDatabase()
{
    // Get the text value
    var textValue = document.getElementById("textInput").value;

    // If the correct text is entered...
    if(textValue === "ClearDatabase")
    {
        // Set the url
        var url = new URL("http://localhost:8080/admin");

        // Send the request
        $.ajax({
            url: url,
            headers: 
            {
                "Content-Type": "application/json"
            },
            type: 'Delete',
            success: function(data)
            {
                // If the clearing was successful...
                if(data.status)
                    alert("Database was cleared successfully.");
                else
                    alert("Database clearing has failed.");
            }
        });    
    }
}