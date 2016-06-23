<?php
  session_start();
  if(!isset($_SESSION['cliEmail']))         
    header("Location: logReg.php");


    $servername = "mysql.cs.orst.edu";
    $username = "cs340_predoviv";
    $password = "4723";
    $dbName = "cs340_predoviv";
    // CONNECT THE DESTROYEROFWORLDS
    $finalDB = new mysqli($servername, $username, $password, $dbName);
    //CHECK CONNECTION
    if($finalDB->connect_error){
        echo "<div>Error:    " . $finalDB->connect_errno . "  " . $finalDB->connect_error."</div>";
    }
?>		



 


<?php
  //Query to fill table with values only from this client
  $client = $_SESSION['cliID'];
  $showVids = $finalDB ->query("SELECT * FROM Documentation WHERE ClientID = '$client' ORDER BY DateRecieved DESC");
  
  if ($showVids == 0)
  {
    die(mysqli_error($finalDB));    
  }
    
  
  
  
  function displayTable($showVids)
  {
     echo "<table id='data' class='pure-table' border='1'><tr><th>  DocID  </th><th>  Date Recieved  </th><th> Media Type </th><th> Description </th><th>  File  </th></tr>";
      // output data of each row
     if ($showVids->num_rows > 0) {
       while($row = $showVids->fetch_assoc())
       {      
          $link_address = $row["Link"];   
                //echo "<button type='button'>Click Me!</button>";          
               //This works like magic, everything in the right place all on one line.
         echo "<tr class='pure-table-odd'><td id='target' class='normals' >".$row["DocID"]."</td><td >".$row["DateRecieved"]."</td><td>".$row["MediaType"]."</td><td>".$row["Description"]."</td>
         <td>  
          <a href='$link_address'>File</a>
        </td>    
        </tr>";
      }
      echo "</table>";
      } else {
      echo "0 results";
      }
  }            
   
      
?>





<!DOCTYPE html>
<title>DABase</title>
<html lang="en">
<head>
        <meta charset="utf-8" />
        <title>Video Interface</title>
        <style>
            wrn {
            color: #f00;
            }
        </style>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
        <link rel="stylesheet" type="text/css" href="Styling.css">
        <link rel="stylesheet" href="http://yui.yahooapis.com/pure/0.6.0/pure-min.css">
  <script type="text/javascript" src="Usage.js"></script>
        </style>
</head>






<body>
        
    
  <div id = "box-form">
    <fieldset>
    <legend>Add a new document:</legend>
        <form class="pure-form" action="clientAppts.php" method="post">
             <input type="date" name="DateRec">Start Date<br>
             <input size="16" type="text" name="addFile">File Link<br>
             <input size="16" type="text" name="addMediaType">Media Type<br>
             <input size="16" type="text" name="addDescription">Description<br>
             <input type="submit" name="addProj"><br>   
        </form>
        
    </fieldset>
  </div>
            <br>
<a class="pure-button pure-button-primary" href="Logout.php">Logout</a>
    </body>

</html>




<?php
  displayTable($showVids); 
?>





