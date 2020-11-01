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