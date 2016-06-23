<?php
  session_start();
  if(!isset($_SESSION['empName']))         
    header("Location: logReg.php");


    $servername = "mysql.cs.orst.edu";
    $username = "cs340_predoviv";
    $password = "4723";
    $dbName = "cs340_predoviv";
    // CONNECT THE DESTROYEROFWORLDS
    $finalDB = new mysqli($servername, $username, $password, $dbName);
    $conn2 = new mysqli($servername, $username, $password, $dbName);
    //CHECK CONNECTION
    if($finalDB->connect_error){
        echo "<div>Error:    " . $finalDB->connect_errno . "  " . $finalDB->connect_error."</div>";
    }
?>    



<?php
//FINISH ADD NEW DOCUMENT. FINISH SEE EMPLOYEES WORKLOAD

  //Query to fill table with values only from this client
  $employee = $_SESSION['empID'];
  $showProjects = $finalDB ->query("SELECT * FROM Work 
                                    INNER JOIN Clients on Work.CID = Clients.CID 
                                    LEFT JOIN Job on Work.WID = Job.WID
                                    LEFT JOIN Documentation on Job.DocID = Documentation.DocID");
  
  $showEmps = $finalDB ->query("SELECT * FROM EMPLOYEES");
  $showClients = $finalDB ->query("SELECT * FROM Clients");


   $empName = $_POST["empWorkName"];
/* create a prepared statement */
if ($empWorker = $finalDB ->query("SELECT * FROM EMPLOYEES where Name=? 
                                   INNER JOIN WORK_On on EMPLOYEES.EID = WORK_On.EID
                                   INNER JOIN WORK on WORK_ON.EID = WORK.EID")) 
{
    /* bind parameters for markers */
    $empWorker->bind_param("s", $empName);
    /* execute query */
    $empWorker->execute();
    /* close statement */
    $stmt->close();
}
  function displayWorkLoad($empWorker)
  {
     echo "<div id = 'box-formd'><table id='data' class='pure-table' border='1'><tr>
     <th> Employee Name </th><th> Completion Date </th>
     <th> Work Type </th><th> Customer </th>
     <th> Documentation Description</th><th>Doc Link</th></tr>";
      // output data of each row
     echo"<p><strong>Here is the work history for</strong></p>".$empName;

     if ($empWorker->num_rows > 0) {
       while($row = $empWorker->fetch_assoc())
       {      
         $linky = $row["Link"];
         echo "<tr class='pure-table-odd'><td id='target' class='normals' >".$row["DateRequested"]."</td>
         <td >".$row["CompletionDate"]."</td>
         <td>".$row["WorkType"]."</td>
         <td>".$row["ClientName"]."</td> 
         <td>".$row["Description"]."</td>
         <td><a class='pure-button' href='$linky'>File</a></td>
         
        </tr>";
      }
      echo "</table></div>";
      } else {
      echo "0 results";
      }
  }  


  if(isset($_POST["delEmp"]))
  {//Still need to make sure this works.
    $delID = $_POST["delEmp"];
    $DeleteEMP = $finalDB ->query("DELETE * FROM EMPLOYEES WHERE CID = '$delID'");
  }


  function displayTable($showProjects)
  {
     echo "<div id = 'box-formd'><table id='data' class='pure-table' border='1'><tr>
     <th> Date Requested </th><th> Completion Date </th>
     <th> Work Type </th><th> Customer </th>
     <th> Documentation Description</th><th>Doc Link</th></tr>";
      // output data of each row
     echo"<p><strong>Note: Services have no File associated with them.</strong></p>";
     if ($showProjects->num_rows > 0) {
       while($row = $showProjects->fetch_assoc())
       {      
         $linky = $row["Link"];
         echo "<tr class='pure-table-odd'><td id='target' class='normals' >".$row["DateRequested"]."</td>
         <td >".$row["CompletionDate"]."</td>
         <td>".$row["WorkType"]."</td>
         <td>".$row["ClientName"]."</td> 
         <td>".$row["Description"]."</td>
         <td><a class='pure-button' href='$linky'>File</a></td>
         
        </tr>";
      }
      echo "</table></div>";
      } else {
      echo "0 results";
      }
  }            
         
  function displayEmps($showEmps)
  {
     echo "<div id = 'box-formd'><table id='data' class='pure-table' border='1'><tr><th>  Name  </th><th> Phone Number </th><th> Delete Employee </th></tr>";
      // output data of each row
     if ($showEmps->num_rows > 0) {
       while($row = $showEmps->fetch_assoc())
       {        
         echo "<tr class='pure-table-odd'><td id='target' class='normals' >".$row["Name"]."</td><td >".$row["PhoneNumber"]."</td>
         <td> 
          <form class='pure-form' action='Appointments.php' method='post'> 
          <button type='submit' class='pure-button pure-button-primary' name='delEmp' value=".$row["EID"].">Delete Employee</button>
          </form> 
        </td>    
        </tr>";
      }
      echo "</table></div>";
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
        </style>
</head>






<body>
<div class="page-wrap">
  <div id = "box-form">
    <fieldset>
    <legend>Add a new document:</legend>
        <form class="pure-form" action="Appointments.php" method="post">
             <input type="date" name="DateRec">Start Date<br>
             <input size="16" type="text" name="addFile">File Link<br>
             <input size="16" type="text" name="addMediaType">Media Type<br>
             <input size="16" type="text" name="addDescription">Description<br>
             <input type="submit" name="addProj"><br>   
        </form>
        
    </fieldset>
  </div>
            <br>

<div class="pure-menu pure-menu-horizontal">

    <ul class="pure-menu-list">
       
        <li class="pure-menu-item">
              <form  id = "box-form2" class="pure-form" action="Appointments.php" method="post">
                   <button type="submit" class="pure-button pure-button-primary" name="seeProj">See Work</button>   
              </form>
        </li>

        <li class="pure-menu-item">
              <form class="pure-form" action="Appointments.php" method="post">
                   <button type="submit" class="pure-button pure-button-primary" name="seeEmps">Manage Employees</button>   
              </form>
        </li>

        <li class="pure-menu-item">
              <div id = "box-form2">          
              <a class="pure-button pure-button-primary" href="Logout.php">Logout</a>
              </div> 
        </li> 

        <li class="pure-menu-item">
              <fieldset >
              <legend>See Employee's Current Workload:</legend>
                <form class="pure-form" action="Appointments.php" method="post">
                     <input size="16" type="text" name="empWorkName">Employee<br>
                     <button type="submit" class="pure-button pure-button-primary" name="empWork">Submit Name</button>   
                </form>
              </fieldset>
        </li> 
    </ul>
</div>

<?php
    if (isset($_POST['seeEmps']))
  {
    displayEmps($showEmps);
  }
  
    if (isset($_POST['seeProj']))
  {
    displayTable($showProjects);
  }
    if (isset($_POST['empWorkName']))
  {
    displayWorkLoad($empWorker);
  }

?>

</div>
  <footer class="blog-footer site-footer" >
    <p>Spanish-Services Management System</p>
    <p>
      <a href="#">Back to top</a>
    </p>
  </footer>



  </body>

</html>





