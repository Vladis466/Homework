<?php
  session_start();
    $servername = "mysql.cs.orst.edu";
    $username = "cs340_predoviv";
    $password = "4723";
    $dbName = "cs340_predoviv";
    // CONNECT THE DESTROYEROFWORLDS
    $finalDB = new mysqli($servername, $username, $password, $dbName);
    //CHECK CONNECTION
    if($finalDB->connect_error){
        //echo "<div>Error:    " . $finalDB->connect_errno . "  " . $finalDB->connect_error."</div>";
    }
//Checks to see if the user entered an email and a password 

  if ((isset($_POST['empName'])) && (isset($_POST['empPassword'])))
  {
      //sets a variable equal to the password the user entered
      $passwordEntered=$_POST['empPassword'];
      //sets a variable equal to the email that the user entered
      $empNameEntered=$_POST['empName'];
      //looks in the table user table for a match 
        $query = "SELECT * FROM EMPLOYEES WHERE Password='$passwordEntered' and Name='$empNameEntered'";
        $result = mysqli_query($finalDB, $query);
        //someone was found
        if (mysqli_num_rows($result) == 1)
        {
              // The log-in is OK so set the user ID and username session vars (and cookies), and redirect to the home page
            $row = mysqli_fetch_array($result);
            $_SESSION['password'] = $row['Password'];
            $_SESSION['empName'] = $row['Name'];
            $_SESSION['EmpID'] = $row['EID'];
            header("Location: Appointments.php"); 
        }
  }  

  if ((isset($_POST['cliEmail'])) && (isset($_POST['cliPassword'])))
  {
      
      //sets a variable equal to the password the user entered
      $cliPassEntered=$_POST['cliPassword'];
      //sets a variable equal to the email that the user entered
      $cliEmailEntered=$_POST['cliEmail'];
      //looks in the table user table for a match 
        $query = "SELECT * FROM Clients WHERE Cpassword='$cliPassEntered' and Email='$cliEmailEntered'";
        $result = mysqli_query($finalDB, $query);
        //someone was found
        if (mysqli_num_rows($result) == 1)
        {
            
              // The log-in is OK so set the user ID and username session vars (and cookies), and redirect to the home page
            $row = mysqli_fetch_array($result);
            $_SESSION['cliPassword'] = $row['Cpassword'];
            $_SESSION['cliEmail'] = $row['Email'];
            $_SESSION['cliID'] = $row['CID']; 
            header("Location: clientApps.php"); 
        }

  }  
?>




<?php
  if (mysqli_num_rows($result) == 0 && $_SERVER['REQUEST_METHOD'] === 'POST') 
  {
    // The username/password are incorrect so set an error message
    echo "<p align='center' style='color:red'>Sorry, you must enter a valid name and password to log in.</p>";
    session_destroy();
  }  

  mysqli_free_result($result);
  mysqli_close($finalDB);  
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

<p align="center"><b><font size="6">Providing Spanish Services</font></b>.</p>



<ul class="nav nav-tabs">
  <li class="active"><a data-toggle="tab" href="#home">Employee Login</a></li>
  <li><a data-toggle="tab" href="#menu1">Client Login</a></li>
</ul>

<div class="tab-content">
  <div id="home" class="tab-pane fade in active">
    
    <div class="container">

      <form class="form-signin" method='post' action='logReg.php'>
        <h2 class="form-signin-heading">Employee Login</h2>
        <label for="inputEmail" class="sr-only">User Name</label>
        <input type="text" id="inputName" name="empName" class="form-control" placeholder="Username" required autofocus>
        <label for="inputPassword" class="sr-only">Password</label>
        <input type="password" id="inputPassword" name="empPassword" class="form-control" placeholder="Password" required>
        <div class="checkbox">
          <label>
            <input type="checkbox" value="remember-me"> Remember me
          </label>
        </div>
        <button class="btn btn-lg btn-primary btn-block" type="submit">Sign in</button>
      </form>

    </div> <!-- /container -->
  </div>


  <div id="menu1" class="tab-pane fade">
    <div class="container">

      <form class="form-signin" method='post' action='logReg.php'>
        <h2 class="form-signin-heading">Client Login</h2>
        <label for="inputEmail" class="sr-only">Email address</label>
        <input type="email" id="cliEmail" name="cliEmail" class="form-control" placeholder="Email address" required autofocus>
        <label for="inputPassword" class="sr-only">Password</label>
        <input type="password" id="cliPassword" name="cliPassword" class="form-control" placeholder="Password" required>  
        <div class="checkbox">
          <label>
            <input type="checkbox" value="remember-me"> Remember me
          </label>
        </div>        
        <button class="btn btn-lg btn-primary btn-block" id="derp" type="submit">Login</button>
      </form>

    </div> <!-- /container -->
  </div>





  


  </body>

</html>