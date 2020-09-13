function Login()
{
    // Initialize the error status
    var error = false;

    // Get the username
    var username = document.getElementById("username").value;

    // If the username is empty...
    if(username.length == 0)
    {
        // Set the error message
        document.getElementById("usernameLabel").innerHTML = "Username can't be empty.";

        // Set the error status
        error = true;
    }
    else
    {
        // Set the error message
        document.getElementById("usernameLabel").innerHTML = "";
    }

    // Get the password
    var password = document.getElementById("psw").value;

    // If the username is empty...
    if(password.length == 0)
    {
        // Set the error message
        document.getElementById("passwordLabel").innerHTML = "Password can't be empty.";

        // Set the error status
        error = true;
    }
    else
    {
        // Set the error message
        document.getElementById("passwordLabel").innerHTML = "";
    }

    // If there isn't an error
    if(!error)
    {
        // Hash the password
        var hashedPassword = CryptoJS.SHA256(password).toString(CryptoJS.enc.Hex);
        
        // Set the request body
        var requestBody = JSON.stringify(
        {
            "username" : username,
            "hashedPassword" : hashedPassword
        });

        // Set the url
        var url = new URL("http://localhost:8080/login");

        // Send the request
        $.ajax({
            url: url,
            headers: 
            {
                "Content-Type": "application/json"
            },
            data: requestBody,
            type: 'POST',
            success: function(data)
            {
                // If the user was validated...
                if(data.validation)
                {
                    // Set the error message
                    document.getElementById("validationLabel").innerHTML = "";

                    // Set the user's location id
                    localStorage.setItem("locationId", data.locationId);
                    
                    // Set the user id
                    localStorage.setItem("id", data.id);
                    
                    // Redirect to the user main page
                    window.location.href='../UserMainPage/UserMainPage.html';
                }
                else
                {
                    // Set the error message
                    document.getElementById("validationLabel").innerHTML = "Invalid username-password combination.";
                }
            }
        });
    }
}