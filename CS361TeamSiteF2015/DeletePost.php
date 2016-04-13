<?php
	session_start();
	include 'ConnectHeader.php';
	if(isset($_SESSION['UID']))
	{
		$UID=$_SESSION['UID'];
		//delete hte name parameter
		//$sql= "SELECT PID, Title, Author, ISBN, Price, Description FROM Posts WHERE UserName='$UserName'";
		$sql= "SELECT * FROM Posts WHERE UID='$UID'";
		$result = mysqli_query($finalDB, $sql);
		//the number of rows is greater than zero, so you can begin to output their data
		if (mysqli_num_rows($result) > 0) 
		{
			echo "<table class='tableCenter'>";
			echo "<tr>";
			echo "<th>PID</th>";
			echo "<th>Book Name</th>";
			echo "<th>Price</th>";
			echo "<th>Comment</th>";
		
			
			
			echo "</tr>";
			// output data
			while($row = mysqli_fetch_assoc($result))
			{
				print'<tr>
				<td> '. $row['PID'] . '</td>
				<td> '. $row['BookName'] .' </td>
				<td> '. $row['Price'] .' </td>
				<td> '. $row['Comment'] .' </td>
				
				
				
				<td>
                 <form  onsubmit="return checkForm(this);" method="post">
                      <input type="hidden" value="'.$row['PID'].'" name="id">
                      <input type="submit" value="Delete" name="delete">
                 </form>
				</td>
				</tr>';
			}
			echo "</table>";
		} 
	
		else 
		{
			//There are now rows in the table, so output that their are 0 entries in the table
			echo "0 results you have not created any posts";
		}
		mysqli_close($finalDB);
	}
	else
	{
		echo "You need to login first before you can delete a post!";
	}
?> 

<?php
if (isset($_POST['delete'])) 
{
	//information required for connecting to the database
	$dbhost = "oniddb.cws.oregonstate.edu";
    $dbuser = "predoviv-db";
    $dbpass = "tTsRu5R7jR3knbgX";
    $dbname = "predoviv-db";
	// Create connection
	$dbc = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
	
	$postID=$_POST['id'];
	//echo "The post id that was deleted was $postID";
	// sql to delete a record
	$sql = "DELETE FROM Posts WHERE PID='$postID'";

if (mysqli_query($dbc, $sql)) 
{
    echo "Record $postID deleted successfully";
} 
else 
{
    echo "Error deleting record: " . mysqli_error($dbc);
}
	mysqli_close($dbc);
}
?>

