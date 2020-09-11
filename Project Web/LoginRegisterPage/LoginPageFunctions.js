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

    // If there isn't an error
    if(!error)
    {
        // Initialize the request body
        var requestBody = 
        {
            "username" : username,
            "password" : CryptoJS.SHA256(password).toString(CryptoJS.enc.Hex)
        };

        // Initialize the request
        var httpRequest = new XMLHttpRequest();

        httpRequest.open("GET", "http://localhost:8080/login", true);
        
        httpRequest.setRequestHeader('Content-Type', 'application/json');
        
        httpRequest.onreadystatechange = function() 
        {

            if (this.readyState == 4) 
            {
                var response = JSON.parse(this.response);
                console.log(response);
                document.getElementById("passwordLabel").innerHTML = response;
            }
        };

        httpRequest.send(JSON.stringify(requestBody));
    }
}

function passwordEquals()
{
    var password = document.getElementById("pasw").value;
    var repeatedPassword = document.getElementById("paswr").value;
    if((password.length < 8) || (repeatedPassword.length < 8))
    {
        document.getElementById("passwordtip").innerHTML = "The passwords must be between 8 and 16 characters";
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

function ValidateRegistration()
{
    var username = document.getElementById("usrname").value;
    if(username.length != 0)
    {
        document.getElementById("usrnametip").innerHTML = "";
        var firstName = document.getElementById("firstname").value;
        if(firstName.length != 0)
        {
            document.getElementById("firstnametip").innerHTML = "";
            var lastName = document.getElementById("lastname").value;
            if(lastName.length != 0)
            {
                document.getElementById("lastnametip").innerHTML = "";
                if(passwordEquals() == true)
                {
                    var email = document.getElementById("email").value;
                    var regex = /[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,4}$/g;
                    if(email.match(regex))
                    {
                        document.getElementById("emailtip").innerHTML = "";
                        alert("Success");
                        return true;
                    }
                    else
                    {        
                        document.getElementById("emailtip").innerHTML = "Enter a valid email.";
                        document.getElementById("lastname").focus();
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                document.getElementById("lastnametip").innerHTML = "Last name can't be empty.";
                document.getElementById("lastname").focus();
                return false;
            }
        }
        else
        {
            document.getElementById("firstnametip").innerHTML = "First name can't be empty.";
            document.getElementById("firstname").focus();
            return false;
        }
    }
    else
    {
        document.getElementById("usrnametip").innerHTML = "Username can't be empty.";
        document.getElementById("usrname").focus();
        return false;
    }
}

function SwitchtoRegisterForm()
{
    HideElementbyId("userForm");
    ShowupElementbyId("registerForm");
}

function SwitchtoLoginForm()
{
    HideElementbyId("passwordForm");
    HideElementbyId("registerForm");
    ShowupElementbyId("userForm");
}

function HideElementbyId(id)
{
    var element = document.getElementById(id);
    if (element.style.display != "none") 
    {
      element.style.display = "none";
    }
}

function ShowupElementbyId(id)
{
    var element = document.getElementById(id);
    if (element.style.display != "block") 
    {
        element.style.display = "block";
    }
}