<?php
include 'ConnectHeader.php';

$sql = "SELECT PID, BookName, Price, Comment FROM Posts WHERE UID='1'";
$result = mysqli_query($finalDB, $sql);
if(mysqli_num_rows($result) == 0)
{
	echo '<p class="error">You have not created any posts</p>';
}
else
{
	echo "<table>
	 <tr>
	 <th>PID</th>
	 <th>Book Name</th>
	 <th>Price</th>
	 <th>Comment</th>
	 </tr>";
	 while($row = mysqli_fetch_array($result))
	{
		 echo "<tr>";
		 echo "<td>" . $row['PID'] . "</td>";
		 echo "<td>" . $row['BookName'] . "</td>";
		 echo "<td>" . $row['Price'] . "</td>";
		 echo "<td>" . $row['Comment'] . "</td>";
		 echo "</tr>";
	 }
	 echo "</table>";
}
mysqli_close($finalDB);
 ?>
