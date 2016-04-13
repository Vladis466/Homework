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
<title>results woo</title>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" integrity="sha512-dTfge/zgoMYpP7QbHy4gWMEGsbsdZeCXz7irItjcC3sPUFtf0kuFbDz/ixG7ArTxmDjLXDmezHubeNikyKGVyQ==" crossorigin="anonymous">
<!-- Optional theme -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css" integrity="sha384-aUGj/X2zp5rLCbBxumKTCw2Z50WgIr1vs/PFN4praOTvYXWlVyh2UtNUU0KAUhAX" crossorigin="anonymous">
<!-- Latest compiled and minified JavaScript -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js" integrity="sha512-K1qjQ+NcF2TYO/eI3M6v8EiNYZfA95pQumfvcVrTHtwQVDG+aHRqLi/ETn2uB+1JqwYqVG3LIvdm9lj6imS/pQ==" crossorigin="anonymous"></script>
<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
<!--[if lt IE 9]>
<script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
<script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
<![endif]-->
</head>

<body style="background-color: lavender;">
<div class="col-md-1"></div>


<?php
    session_start();
    $servername = "oniddb.cws.oregonstate.edu";
    $username = "predoviv-db";
    $password = "tTsRu5R7jR3knbgX";
    $dbName = "predoviv-db";
    $search = $_POST['searchquery'];
    
    $finalDB = new mysqli($servername, $username, $password, $dbName);
    //CHECK CONNECTION
    if($finalDB->connect_error){
        echo "<div>Error:    " . $finalDB->connect_errno . "  " . $finalDB->connect_error."</div>";
    }
    echo "<p> hello " . $col . "</p>";
    echo "<p> hi" . $search . "</p>";
    $query = "SELECT * FROM Posts WHERE BookName = '$search'";
    //var_dump($query);
    var_dump($finalDB->query);
    if(!($result = $finalDB->query($query))){
        echo "<p> ahhhhh</p>";
        printf("Error: ", $finalDB->error);
    }

    var_dump($result);


    /*echo "<div class=\"col-md-10\">"
    echo "<h2 class=\"text-center\"> Here's what we found...</h2>";
    while($row = mysqli_fetch_array($result)){
        echo "<h3 class=\"text-center\">Book Title: ";
        echo $row['Title'] . "</h3>";
        echo "<h5 class=\"text-left\">Author: ";
        echo $row['Author'] . "</h5>";
        echo "<section class=\"text-left\">ISBN: ";
        echo $row['ISBN'] . "</section>";
        echo "<section class=\"text-right\">Price: $";
        echo $row['Price'] . "</section>";
        echo "<blockquote>Description: ";
        echo $row['Post_Body'] . "</blockquote>";
        echo "<br />";
        echo "<br />";
        echo "<section class=\"text-left\">POST ID: ";
        echo $row['Post_ID'] . "                      UID: " . $row['UID'];
        echo "<br />";
    }
    echo "</div>";*/
    
?>

