function passwordEquals(password, repeatedPassword)
{
    if((password.length < 8) || (repeatedPassword.length < 8))
    {
        document.getElementById("passwordLabel").innerHTML = "The passwords must be between 8 and 16 characters";
    }
    else
    {
        if(password == repeatedPassword)
        {    
            var regex = /^(?=.*[A-Z])(?=.*?[0-9])(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,16}$/g;
            if(password.match(regex))
            {
                document.getElementById("passwordtip").innerHTML = "";
                return true;
            }
            else
            {
                document.getElementById("passwordtip").innerHTML = "The passwords must contain at least one uppercase letter, one number and one special character.";
            }
        }
        else
        {
            document.getElementById("passwordtip").innerHTML = "The passwords must be the same.";
            return false;
        }
    }
}

function Register()
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

    // Get the first name
    var firstName = document.getElementById("firstName").value;

    if(firstName.length == 0)
    {
        // Set the error message
        document.getElementById("firstNameLabel").innerHTML = "First name can't be empty.";

        // Set the error status
        error = true;
    }
    else
    {
        // Set the error message
        document.getElementById("firstNameLabel").innerHTML = "";
    }

    // Get the last name
    var lastName = document.getElementById("lastName").value;

    if(lastName.length == 0)
    {
        // Set the error message
        document.getElementById("lastNameLabel").innerHTML = "Last name can't be empty.";

        // Set the error status
        error = true;
    }
    else
    {
        // Set the error message
        document.getElementById("lastNameLabel").innerHTML = "";
    }

    // Get the password
    var password = document.getElementById("psw").value;

    // Get the repeated password
    var repeatedPassword = document.getElementById("rpsw").value;

    // If both passwords are valid..
    if(passwordEquals(password, repeatedPassword))
    {
        // Set the error message
        document.getElementById("lastNameLabel").innerHTML = "";
    }
    else
    {
        // Set the error message
        document.getElementById("passwordLabel").innerHTML = "The passwords don't match the criteria.";

        // Set the error status
        error = true;
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
            "hashedPassword" : hashedPassword,
            "firstName" : firstName,
            "lastName" : lastName
        });

        // Set the url
        var url = new URL("http://localhost:8080/signup");

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
                    // Set the user's location id
                    localStorage.setItem("locationId", data.locationId);
                    
                    // Set the user id
                    localStorage.setItem("id", data.id);
                    
                    // Redirect to the user main page
                    window.location.href='../UserMainPage/UserMainPage.html';
                }
            }
        });
    }
}