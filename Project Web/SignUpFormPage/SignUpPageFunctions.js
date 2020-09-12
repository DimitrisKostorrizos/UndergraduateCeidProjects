function passwordEquals()
{
    var password = document.getElementById("psw").value;
    var repeatedPassword = document.getElementById("rpsw").value;

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
    var username = document.getElementById("username").value;
    
    if(username.length != 0)
    {
        document.getElementById("usernameLabel").innerHTML = "";

        var firstName = document.getElementById("firstName").value;

        if(firstName.length != 0)
        {
            document.getElementById("firstnametip").innerHTML = "";
            var lastName = document.getElementById("lastname").value;
            if(lastName.length != 0)
            {
                document.getElementById("lastnametip").innerHTML = "";
                if(passwordEquals())
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