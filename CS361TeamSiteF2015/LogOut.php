<?php
	session_start();
	$old_user = $_SESSION['UID'];
	unset($_SESSION['UID']);
	session_destroy();
    session_start(); 
    header("Location: LoginReg.php");
?>
<!DOCTYPE html>
<html>
<head>
		<link rel="stylesheet" href="ProjectStyle.css">
		<meta charset = "utf-8" />
</head>
<body>
	<!--<h1> Log Out Page</h1>-->
	<?php
		if (!empty($old_user)) 
		{
			echo "<p>";
			echo 'User: '.$old_user.' is logged out';
			echo "</p>";
		} else {
			echo "<p>";
			echo 'You were not logged in!';
			echo "</p>";
		}
	?>

</body>
</html>
