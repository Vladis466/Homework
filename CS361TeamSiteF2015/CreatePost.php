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
    
	<script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
	<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.11.1/jquery-ui.min.js"></script>
	
	<style>
		.ui-dialog-titlebar {
			display: none;
		}
	</style>
    
    <title>Create a Post</title>
    
    <!-- Bootstrap -->
	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" integrity="sha512-dTfge/zgoMYpP7QbHy4gWMEGsbsdZeCXz7irItjcC3sPUFtf0kuFbDz/ixG7ArTxmDjLXDmezHubeNikyKGVyQ==" crossorigin="anonymous">
	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css" integrity="sha384-aUGj/X2zp5rLCbBxumKTCw2Z50WgIr1vs/PFN4praOTvYXWlVyh2UtNUU0KAUhAX" crossorigin="anonymous">
	<!-- Latest compiled and minified JavaScript -->
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js" integrity="sha512-K1qjQ+NcF2TYO/eI3M6v8EiNYZfA95pQumfvcVrTHtwQVDG+aHRqLi/ETn2uB+1JqwYqVG3LIvdm9lj6imS/pQ==" crossorigin="anonymous"></script>
  </head>
  
  
  
  <body>
  	
  	<ul class="nav navbar-nav">
    <li class="active"><a href="indx.php">Home</a></li>
    <li><a href="CreatePost.php">Create a Post</a></li>
    <li><a href="ShowUserPosts.php">See your Posts</a></li>
	</ul><br><br>
  	<div id="loading"><img id="loading" src="http://www.schultzlawoffice.com/img/loading/loading-x.gif"></div>
  	<script>
		/*
		 * jQuery UI Dialog: Open Dialog on Click
		 * http://salman-w.blogspot.com/2013/05/jquery-ui-dialog-examples.html
		 */
		$(function() {
			$("#loading").dialog({
				autoOpen: false,
				modal: true
			});
		});
	</script>
    
    <div class="container-fluid">

      <form class="form-createpost" method='post' action="CreatePost.php" onsubmit="$('#loading').dialog('open');">
        <h2 class="form-createpost-heading">Create a Post</h2>
        
        <label for="postTitle" class="sr-only">Title</label>
        <input type="text" id="postTitle" name="postTitle" class="form-control" placeholder="Title" required autofocus>
        
        <label for="ISBN" class="sr-only">ISBN Number</label>
        <input type="text" id="ISBN" name="ISBN" class="form-control" placeholder="ISBN #">
        
        <label for="price" class="sr-only">Price</label>
        <input type="number" id="price" name="price" class="form-control" placeholder="Price" min=0 step=.01>
        

<div class="form-group">
  <label for="schoolChoice">Select your School</label>
  <select name="schoolChoice" class="form-control" id="schoolChoice">
	    <option value='oregon'>University of Oregon</option>
	    <option value='oregonstate'>Oregon State University</option>
	    <option value='OSUcascades'>OSU cascades</option>
	    <option value='Washington'>University of Washington</option>
  </select>
</div>


        <label for="postBody" class="sr-only">Description</label>
        <textarea name="postBody" id="postBody" class="form-control" placeholder="Description" rows=15></textarea>
        
        <button class="btn btn-lg btn-primary btn-block" type="submit">Save</button>
      </form>

    </div> <!-- /container -->

  </body>
</html>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {


	$servername = "oniddb.cws.oregonstate.edu";
    $username = "predoviv-db";
    $password = "tTsRu5R7jR3knbgX";
    $dbName = "predoviv-db";
    
    $finalDB = new mysqli($servername, $username, $password, $dbName);
    
    if($finalDB->connect_error){
        echo "<div>Piess Error:    " . $finalDB->connect_errno . "  " . $finalDB->connect_error."</div>";
    }

    	
	session_start();
	

	
    $uid = $_SESSION['UID'];
	$pid = rand(0, getrandmax());
	$post_title = $_POST['postTitle'];
	//$isbn = str_replace("-", "", $_POST['ISBN']);
	$price = $_POST['price'];
	$post_body = $_POST['postBody'];
	$school = $_POST['schoolChoice'];
	//$author = NULL;
	
	/*$url = "http://www.isbndb.com/api/v2/json/YYH6FGB2/book/$isbn";
	if ($isnb != "") {
		$response = file_get_contents($url);
		$json = json_decode($response);
		
		$author = $json->data[0]->author_data[0]->name;
		//$title = $json->data[0]->title;
		$edition = $json->data[0]->edition_info;
	}*/
	
	/*if ($author == NULL) {
		$author = "";
	}*/
	
	$query = "INSERT INTO Posts (PID, BookName, Price, Comment, UID, School) VALUES(?, ?, ?, ?, ?, ?)";
	$statement = $finalDB->prepare($query);

	//bind parameters for markers, where (s = string, i = integer, d = double,  b = blob)
	$statement->bind_param('isdsis', $pid, $post_title, $price, $post_body, $uid, $school);
	$statement->execute();

    if ($query == 0)
      die(mysqli_error($finalDB)); 
		//print 'Success! ID of last inserted record is : ' . $statement->insert_id . '<br />'; 
		$url = 'http://' . $_SERVER['HTTP_HOST'];			// Get the server
		$url .= rtrim(dirname($_SERVER['PHP_SELF']), '/\\');// Get the current directory
		$url .= '/ShowUserPosts.php';						// <-- Your relative path
		$statement->close();
		header('Location: ' . $url, true, 302);
	//}else{
	//	$statement->close();
	//}
	//die(' diiieeeee Error : ('. $finalDB->errno .') '. $finalDB->error);
}
?>
