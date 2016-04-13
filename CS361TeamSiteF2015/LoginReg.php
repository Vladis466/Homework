<?php
  session_start();
  if(isset($_SESSION['UID']))
    header("location: Shopping.php");

include 'ConnectHeader.php';
//Checks to see if the user entered an email and a password 
if ((isset($_POST['email'])) && (isset($_POST['password'])))
{
    //sets a variable equal to the password the user entered
    $passwordEntered=$_POST['password'];
    //sets a variable equal to the email that the user entered
    $emailEntered=$_POST['email'];
    //looks in the table user table for a match 
      $query = "SELECT * FROM Users  WHERE Password='$passwordEntered' and Email='$emailEntered'";
      $result = mysqli_query($finalDB, $query);
      //someone was found
      if (mysqli_num_rows($result) == 1)
      {
            // The log-in is OK so set the user ID and username session vars (and cookies), and redirect to the home page
          $row = mysqli_fetch_array($result);
          $_SESSION['password'] = $row['Password'];
          $_SESSION['email'] = $row['Email'];
		  $_SESSION['UID'] = $row['UID'];
          //session_destroy();
      }
      else 
      {
      // The username/password are incorrect so set an error message
            echo "<p>Sorry, you must enter a valid email and password to log in.</p>";
            session_destroy();
        }
        mysqli_free_result($result);
        mysqli_close($finalDB);
}  
?>
<?php
  if (isset($_SESSION['email'])) 
    {
        echo " <h3> You are logged in as </h3><p> User: ".$_SESSION['email']; 
		echo " <a href='Shopping.php'>Go Shopping!</a>";
		echo " <a href='CreatePost.php'> Make a Post!</a>";
        //echo "<p> <a href='LogOutPage.php'>Log out </a><br />";
    } 
    else 
    {
        if (isset($emailEntered)) 
        {
            // user tried but can't log in
            echo "<h2> Could not log you in </h2>";
        } 
        else 
        {
            // user has not tried
            echo " <h2> You need to log in </h2> ";
        }
    }
?>

<?php 
    $dbhost = "oniddb.cws.oregonstate.edu";
    $dbuser = "predoviv-db";
    $dbpass = "tTsRu5R7jR3knbgX";
    $dbName = "predoviv-db";

	// Create connection 
	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbName);
	// Check connection
	if (!$dbc) {
		die("Connection failed: " . mysqli_connect_error());
	}
	
	if ((isset($_POST['newemail'])) && (isset($_POST['newpassword'])) && (isset($_POST['newusername']))) {
		// Grab the profile data from the POST
		$Username = mysqli_real_escape_string($dbc, trim($_POST['newusername']));
		$Password = mysqli_real_escape_string($dbc, trim($_POST['newpassword']));
		$Email = mysqli_real_escape_string($dbc, trim($_POST['newemail'])); 

		//Check to see if the user entered a password and a user name
		if (!empty($Username) && !empty($Password) && !empty($Email)) {
			// Make sure someone isn't already registered using this username
			$query = "SELECT * FROM Users WHERE username = '$Username'";
			$data = mysqli_query($dbc, $query);

			if (mysqli_num_rows($data) == 0) {
				// The username is unique, so insert the data into the database
				$query = "INSERT INTO Users (username, password, email) VALUES ('$Username', '$Password', '$Email')";
				mysqli_query($dbc, $query);
				//Confirm success with the user
				echo '<p>Your new account has been successfully created. You\'re now ready to log in.</p>';
				//Close the connection
				mysqli_close($dbc);
				exit();
			}
	
			else {
				// An account already exists for this username, so display an error message
				echo '<p class="error">An account already exists for this username. Please use a different address.</p>';
				$Username = "";
			}
		}

		//user did not enter all the information that is required for creating an account, so display an error

	}
  // Create connection 
  $dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbName);
  // Check connection
  if (!$dbc) {
    die("Connection failed: " . mysqli_connect_error());
  }
  
  if ((isset($_POST['newemail'])) && (isset($_POST['newpassword'])) && (isset($_POST['newusername']))) {
    // Grab the profile data from the POST
    $Username = mysqli_real_escape_string($dbc, trim($_POST['newusername']));
    $Password = mysqli_real_escape_string($dbc, trim($_POST['newpassword']));
    $Email = mysqli_real_escape_string($dbc, trim($_POST['newemail'])); 

    //Check to see if the user entered a password and a user name
    if (!empty($Username) && !empty($Password) && !empty($Email)) {
      // Make sure someone isn't already registered using this username
      $query = "SELECT * FROM Users WHERE username = '$Username'";
      $data = mysqli_query($dbc, $query);

      if (mysqli_num_rows($data) == 0) {
        // The username is unique, so insert the data into the database
        $query = "INSERT INTO Users (username, password, email) VALUES ('$Username', '$Password', '$Email')";
        mysqli_query($dbc, $query);
        //Confirm success with the user
        echo '<p>Your new account has been successfully created. You\'re now ready to log in.</p>';
        //Close the connection
        mysqli_close($dbc);
        exit();
      }
  
      else {
        // An account already exists for this username, so display an error message
        echo '<p class="error">An account already exists for this username. Please use a different address.</p>';
        $Username = "";
      }
    }

    //user did not enter all the information that is required for creating an account, so display an error

  }
?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="../../favicon.ico">

    <title>Signin</title>

<!-- JQuery -->    
 <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" integrity="sha512-dTfge/zgoMYpP7QbHy4gWMEGsbsdZeCXz7irItjcC3sPUFtf0kuFbDz/ixG7ArTxmDjLXDmezHubeNikyKGVyQ==" crossorigin="anonymous">
<!-- Optional theme -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css" integrity="sha384-aUGj/X2zp5rLCbBxumKTCw2Z50WgIr1vs/PFN4praOTvYXWlVyh2UtNUU0KAUhAX" crossorigin="anonymous">
<!-- Latest compiled and minified JavaScript -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js" integrity="sha512-K1qjQ+NcF2TYO/eI3M6v8EiNYZfA95pQumfvcVrTHtwQVDG+aHRqLi/ETn2uB+1JqwYqVG3LIvdm9lj6imS/pQ==" crossorigin="anonymous"></script>
    <!-- Custom styles for this template -->
    <link href="Styling.css" rel="stylesheet">
    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>

  <body>





<ul class="nav nav-tabs">
  <li class="active"><a data-toggle="tab" href="#home">Login</a></li>
  <li><a data-toggle="tab" href="#menu1">Register</a></li>
</ul>

<div class="tab-content">
  <div id="home" class="tab-pane fade in active">
    
    <div class="container">

      <form class="form-signin" method='post' action='LoginReg.php'>
        <h2 class="form-signin-heading">Please sign in</h2>
        <label for="inputEmail" class="sr-only">Email address</label>
        <input type="email" id="inputEmail" name="email" class="form-control" placeholder="Email address" required autofocus>
        <label for="inputPassword" class="sr-only">Password</label>
        <input type="password" id="inputPassword" name="password" class="form-control" placeholder="Password" required>
        <div class="checkbox">
          <label>
            <input type="checkbox" value="remember-me"> Remember me
          </label>
        </div>
        <div class="hidden" id="nameInput">
        <label for="inputEmail" class="sr-only">User Name</label>
        <input type="text" id="inputName" name="userName" class="form-control" placeholder="Username">
        </div>
        <button class="btn btn-lg btn-primary btn-block" type="submit">Sign in</button>
      </form>

    </div> <!-- /container -->



  </div>
  <div id="menu1" class="tab-pane fade">
    <div class="container">

      <form class="form-signin" method='post' action='LoginReg.php'>
        <h2 class="form-signin-heading">Register here!</h2>
        <label for="inputnewUsername" class="sr-only">Username</label>
        <input type="text" id="newusername" name="newusername" class="form-control" placeholder="Username" required>
        <label for="inputPassword" class="sr-only">Password</label>
        <input type="password" id="newpassword" name="newpassword" class="form-control" placeholder="Password" required>
        <label for="inputEmail" class="sr-only">Email address</label>
        <input type="email" id="newemail" name="newemail" class="form-control" placeholder="Email address" required autofocus>
 
      <div class="form-signin">
      <button class="btn btn-lg btn-primary btn-block" id="derp" type="submit">Register</button>
      </div>
      </form>

    </div> <!-- /container -->
  </div>

  </body>

</html>