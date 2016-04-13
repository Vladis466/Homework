<?php
  session_start();
  if(isset($_SESSION['empName']))
  {         
    header("Location: clientApps.php");
  }  
  echo $_SESSION['empName']; 
?>