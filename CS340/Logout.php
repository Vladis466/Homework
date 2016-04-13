<?php
	session_start();
	session_destroy();
	header("Location: logReg.php");
?>