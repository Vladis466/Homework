<?php 
    session_start(); 
    if(!isset($_SESSION["UID"]))
        header("Location: LoginReg.php");
    
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
        <title>Shoppin lol</title>
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
    <form class="form-signin" method='post' action='LogOut.php'>
        <button class="btn btn-lg btn-primary btn-block" type="submit">Logout</button>
    </form>
<?php
    $servername = "oniddb.cws.oregonstate.edu";
    $username = "predoviv-db";
    $password = "tTsRu5R7jR3knbgX";
    $dbName = "predoviv-db";
    // CONNECT MY ASS
    $finalDB = new mysqli($servername, $username, $password, $dbName);
    //CHECK CONNECTION
    if($finalDB->connect_error){
        echo "<div>Error:    " . $finalDB->connect_errno . "  " . $finalDB->connect_error."</div>";
    }
     //GET SCHOOL
    $locationEmail = $_SESSION['email']; 
    $subject = $locationEmail;
    $pattern = '/@([^.]*)/';
    preg_match($pattern, $subject, $matches);
    $school = $matches[1];
    $_SESSION['school'] = $school;
    echo "<h1>Below are all the entries sold at the following School:".$school."</h1>";   
    $query = "SELECT * FROM Posts
              Where School = '$school'";
    $result = mysqli_query($finalDB, $query) or die("fuck meeeeeeeeee");
    echo "<div class=\"col-md-9\">";
    while($row = mysqli_fetch_array($result)){
        echo "<h3 class=\"text-center\">Book Title: ";
        echo $row['BookName'] . "</h3>";
        echo "<h5 class=\"text-left\">Author: ";
        echo "<section class=\"text-right\">Price: $";
        echo $row['Price'] . "</section>";
        echo "<blockquote>Description: ";
        echo $row['Comment'] . "</blockquote>";
        echo "<br />";
        echo "<br />";
        echo "<section class=\"text-left\">POST ID: ";
        echo $row['PID'] . "                      UID: " . $row['UID'];
        echo "<br />";
		echo "<section class='text-right'><a href='Feedback.php?Seller_ID=" . $row['UID'] . "'>Buy Now!</a></section>";
    }
    echo "</div>";



?>



        <div class="col-md-2">
        <form action="searchresults.php" method="post">
            Search based on "title"
                <label for="searchquery">for </label>
                <input type="text" id="searchquery" name="searchquery" />
                <input type="submit">Search</input>
        </form>
        </div>


<ul class="nav navbar-nav">
    <li class="active"><a href="#">Home</a></li>
    <li><a href="CreatePost.php">Create a Post</a></li>
    <li><a href="ShowUserPosts.php">See your Posts</a></li>
</ul>
        </body>
    </html>