<!DOCTYPE html>
<html>
<body>
<?php
  header("Content-type: text/xml");
  echo "<?xml version='1.0' encoding='UTF-8'?>";
  echo "<note>";
  echo "<from>Jani</from>";
  echo "<to>Tove</to>";
  echo "<message>Remember me this weekend</message>";
  echo "</note>";
// if (isset($_POST['submit'])) { //This one right here checks if the user came here from the submit button.
//   $file = $_FILES['fileToUpload']; //This one right here stores the uploaded file to $file variable.

//   // print_r($file); //This one right here provides us the 'info' we use right below.
//   $file_name = $file['name']; //This one right here stores the name of the file to $file_name variable.
//   $file_tmp_name = $file['tmp_name']; //You can...
//   $file_size = $file['size']; //get this...
//   $file_error = $file['error']; //by your...
//   $file_type = $file['type']; //own.

//   $file_extension = explode('.', $file_name); //This one right here give us the extension of the file that the user uploaded.
//   $file_actual_extension = strtolower(end($file_extension)); //This one right here lowercase all the letters of the extension so as to get what we want.

//   $allowed_extensions = array('json', 'zip'); //This one right here is an array with all the file extensions that users can upload.

//   if (in_array($file_actual_extension, $allowed_extensions)) { //This one right here checks if the extension of the file that the user uploaded is valid.
//     switch ($file_actual_extension) {
//       case 'zip':
//         // This one right here will be the code for zip case.
//         break;

//       case 'json':
//         if ($file_error === 0) { //This one right here checks for more errors through the upload.
//           if ($file_size <= 524288000) { //This one right here limits the size of the file that the user wants yo upload. 1,073,741,824 = exactly 1GB, and 524,288,000 = exactly 500MB.
//             $file_name_new = uniqid('', true).".".$file_actual_extension; //This one right here renames the file that the user wants to upload to something unique so as to avoid having more than one file with the same name.
//             $file_destination = 'uploads/'.$file_name_new; //This one right here finally uploads the file to the destination we want to.

//             move_uploaded_file($file_tmp_name, $file_destination); //This one right here moves the uploaded file from temporary location to the location we want to.

//             header("Location: UserUploadDataPage.html?upload=success");
//             exit();
//           }
//           else {
//             echo "Your file is too big!";
//             header("Location: UserUploadDataPage.html?upload=fail");
//             exit();
//           }
//         }
//         else {
//           echo "There was an error uploading your file!";
//           header("Location: UserUploadDataPage.html?upload=fail1");
//           exit();
//         }
//       }
//     }
//     else {
//       echo "You can't upload files of this type!";
//       // header("Location: UserUploadDataPage.html?upload=fail2");
//       exit();
//     }
//   }
//   else { //This one right here sent the curious user back to home when he tries to enter the include page in other way that from the button I mentioned.
//     header("Location: UserUploadDataPage.html");
//     exit();
//   }
?>
</body>
</html>