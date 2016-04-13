<?php
session_start();
if ($_SERVER['REQUEST_METHOD'] == "GET") {
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
		
		.rating {
			overflow: hidden;
			display: inline-block;
			font-size: 0;
			position: relative;
		}
		.rating-input {
			float: right;
			width: 16px;
			height: 16px;
			padding: 0;
			margin: 0 0 0 -16px;
			opacity: 0;
		}
		.rating:hover .rating-star:hover,
		.rating:hover .rating-star:hover ~ .rating-star,
		.rating-input:checked ~ .rating-star {
			background-position: 0 0;
		}
		.rating-star,
		.rating:hover .rating-star {
			position: relative;
			float: right;
			display: block;
			width: 16px;
			height: 16px;
			background: url('http://kubyshkin.ru/samples/star-rating/star.png') 0 -16px;
		}

	</style>
    
    <title>Rate a Seller</title>
    
    <!-- Bootstrap -->
	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" integrity="sha512-dTfge/zgoMYpP7QbHy4gWMEGsbsdZeCXz7irItjcC3sPUFtf0kuFbDz/ixG7ArTxmDjLXDmezHubeNikyKGVyQ==" crossorigin="anonymous">
	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css" integrity="sha384-aUGj/X2zp5rLCbBxumKTCw2Z50WgIr1vs/PFN4praOTvYXWlVyh2UtNUU0KAUhAX" crossorigin="anonymous">
	<!-- Latest compiled and minified JavaScript -->
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js" integrity="sha512-K1qjQ+NcF2TYO/eI3M6v8EiNYZfA95pQumfvcVrTHtwQVDG+aHRqLi/ETn2uB+1JqwYqVG3LIvdm9lj6imS/pQ==" crossorigin="anonymous"></script>
  </head>
  
  
  
  <body>
  	
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

      <form class="form-createpost" method='post' action="Feedback.php" onsubmit="$('#loading').dialog('open');">
        <h2 class="form-createpost-heading">Rate a Seller</h2>
        
        <span class="rating">
			<input type="radio" class="rating-input"
					id="rating-input-1-5" name="rating-input-1" value="5" />
			<label for="rating-input-1-5" class="rating-star"></label>
			
			<input type="radio" class="rating-input"
					id="rating-input-1-4" name="rating-input-1" value="4" />
			<label for="rating-input-1-4" class="rating-star"></label>
			
			<input type="radio" class="rating-input"
					id="rating-input-1-3" name="rating-input-1" value="3" />
			<label for="rating-input-1-3" class="rating-star"></label>
			
			<input type="radio" class="rating-input"
					id="rating-input-1-2" name="rating-input-1" value="2" />
			<label for="rating-input-1-2" class="rating-star"></label>
			
			<input type="radio" class="rating-input"
					id="rating-input-1-1" name="rating-input-1" value="1" />
			<label for="rating-input-1-1" class="rating-star"></label>
	</span>
		
        <label for="content" class="sr-only">Description</label>
        <textarea name="content" id="content" class="form-control" placeholder="Description" rows=15></textarea>
        
		<input type="hidden" name="Seller_ID" value="<?php echo $_GET["Seller_ID"]; ?>">
		
        <button class="btn btn-lg btn-primary btn-block" type="submit">Save</button>
      </form>

    </div> <!-- /container -->

  </body>
</html>

<?php
} else if ($_SERVER["REQUEST_METHOD"] == "POST") {
	
    $servername = "oniddb.cws.oregonstate.edu";
    $username = "predoviv-db";
    $password = "tTsRu5R7jR3knbgX";
    $dbName = "predoviv-db";
    // CONNECT THE DESTROYEROFWORLDS
    $finalDB = new mysqli($servername, $username, $password, $dbName);
    //CHECK CONNECTION
    if($finalDB->connect_error)
    {
        echo "<div>Error:    " . $finalDB->connect_errno . "  " . $finalDB->connect_error."</div>";
    }
	
	mysqli_report(MYSQLI_REPORT_ALL);
	
	$sellerID = $_POST['Seller_ID'];
	$userID   = $_SESSION['UID'];
	//echo "userID = $userID";
	$stars    = $_POST['rating-input-1'];
	$content  = $_POST['content'];
	
	$query = "INSERT INTO Feedback (Content, User_ID, Seller_ID, Stars) VALUES(?, ?, ?, ?)";
	$statement = $finalDB->prepare($query);

	//bind parameters for markers, where (s = string, i = integer, d = double,  b = blob)
	$statement->bind_param('siii', $content, $userID, $sellerID, $stars);

	if($statement->execute()){
		//print 'Success! ID of last inserted record is : ' . $statement->insert_id . '<br />'; 
		$url = 'http://' . $_SERVER['HTTP_HOST'];			// Get the server
		$url .= rtrim(dirname($_SERVER['PHP_SELF']), '/\\');// Get the current directory
		$url .= '/Shopping.php';							// <-- Your relative path
		$statement->close();
		header('Location: ' . $url, true, 302);
	}else{
		echo "esle<br><br>";
		$statement->close();
	}
	echo var_dump($finalDB->connect_error);
	die('<br><br>Error : ('. $finalDB->errno .') '. $finalDB->error);
}
?>