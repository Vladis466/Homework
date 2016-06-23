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
//FINISH ADD NEW DOCUMENT. FINISH SEE EMPLOYEES WORKLOAD. ADD EID TO EMPLOYEE LISTING AND USE THIS TO QUERY WORKLOAD

  //Query to fill table with values only from this client
  $employee = $_SESSION['empID'];
  $showProjects = $finalDB ->query("SELECT * FROM Work 
                                    INNER JOIN Clients on Work.CID = Clients.CID 
                                    LEFT JOIN Job on Work.WID = Job.WID
                                    INNER JOIN Documentation on Job.DocID = Documentation.DocID
                                    UNION
                                    SELECT * FROM Work 
                                    INNER JOIN Clients on Work.CID = Clients.CID 
                                    LEFT JOIN Job on Work.WID = Job.WID
                                    LEFT JOIN Documentation on Job.DocID = Documentation.DocID");
                                    
  $showEmps = $finalDB ->query("SELECT * FROM EMPLOYEES");
  $showClients = $finalDB ->query("SELECT * FROM Clients");
 


  //INSERT NEW EMPLOYEEE
  if(isset($_POST["addEmp"]))
  {

    $addDoc = $finalDB->prepare("INSERT INTO EMPLOYEES (Name, Password, PhoneNumber, adminPrivs) VALUES (?, ?, ?, ?)");
    $addDoc->bind_param("sssi", $empName, $empPass, $empPhNum, $empAdmin);
    $empName=$_POST["empName"];
    $empPhNum=$_POST["empPhoneNumber"];
    $empPass=$_POST["empPass"];
    $empAdmin=0;
  //https://drive.google.com/file/d/0Byfufr0utaZsVXFWQ0VSODAzcGs/view?usp=sharing
    $addDoc->execute();
    if ($addDoc == 0)
      die(mysqli_error($finalDB)); 
    else
      echo "Succesfully added new employee";
    $addDoc->close();
  }
  


/* SEE EMPLOYEE WORLOAD QUERY*/
  if(isset($_POST["empWork"]))
  {
    $empName = $_POST["empWorkName"];
    $empWorker = $finalDB ->query("SELECT * FROM EMPLOYEES 
                                   INNER JOIN Work_On on EMPLOYEES.EID = Work_On.EID
                                   INNER JOIN Work on Work_On.WID = Work.WID
                                   INNER JOIN Clients on Work.CID = Clients.CID
                                   LEFT JOIN Job on Work.WID = Job.WID
                                   LEFT JOIN Documentation on Job.DocID = Documentation.DocID
                                   WHERE Name='$empName'"); 
    if ($empWorker == 0)
      die(mysqli_error($finalDB));                                   
  }

/* SEE EMPLOYEE WORLOAD DISPLAY DATA*/
  function displayWorkLoad($empWorker, $employeeName)
  {
     echo "<div id = 'box-formd'><table id='data' class='pure-table' border='1'><tr>
     <th> Employee Name </th><th> Completion Date </th>
     <th> Work Type </th><th> Customer </th>
     <th> Documentation Description</th><th>Doc Link</th></tr>";
      // output data of each row
     echo"<p><strong>Work history for: ".$employeeName."</strong></p>";
     echo"<p><strong>Note: Services have no File associated with them.</strong></p>";
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

  //DELETE EMPLOYEE
    if(isset($_POST["delEmp"]))
    {//Still need to make sure this works.
      $delID = $_POST["delEmp"];
      $DeleteEMP = $finalDB ->query("DELETE FROM EMPLOYEES WHERE EID = '$delID'");
      if ($DeleteEMP == 0)
        die(mysqli_error($finalDB));  
    }

  //UPDATE EMPLOYE PHONE NUMBER

    if(isset($_POST["updateEmpPhoneNumber"]))
  {
    $upEmpID = $_POST["updateEmpPhoneNumber"];
    $newNum = $_POST["newNum"];
    echo $newNum;
    echo "BONJORNO";
    $UpdateEMP = $finalDB ->query("UPDATE EMPLOYEES SET PhoneNumber='$newNum' WHERE EID = '$upEmpID'");
    if ($UpdateEMP == 0)
      die(mysqli_error($finalDB));      
  }  
//DISPLAY ACTIVE PROJECTS
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
     echo "<div id = 'box-formd'><table id='data' class='pure-table' border='1'><tr><th>  Name  </th>
     <th> Phone Number </th><th> Delete Employee </th><th> Edit Phone number_format(number) </th></tr>";
      // output data of each row
     if ($showEmps->num_rows > 0) {
       while($row = $showEmps->fetch_assoc())
       {        
         echo "<tr class='pure-table-odd'>
              <td id='target' class='normals' >".$row["Name"]."</td>
              <td >".$row["PhoneNumber"]."</td>
             <td> 
                  <form class='pure-form' action='Appointments.php' method='post'> 
                  <button type='submit' class='pure-button pure-button-primary' name='delEmp' 
                  value=".$row["EID"].">Delete Employee</button>
                  </form> 
            </td>  
             <td> 
                  <form class='pure-form' action='Appointments.php' method='post'>
                  <input size='16' type='text' name='newNum'><br>
                  <button type='submit' class='pure-button pure-button-primary' name='updateEmpPhoneNumber' 
                  value=".$row["EID"].">Change Emp Phone</button>
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
<div class="pure-menu pure-menu-horizontal">

    <ul class="pure-menu-list">
  <li class="pure-menu-item">    
  <div id = "box-form">
    <fieldset>
    <legend>Add a new Employee:</legend>
        <form class="pure-form" action="Appointments.php" method="post">
             <input size="16" type="text" name="empName">Employee Name<br>
             <input size="16" type="text" name="empPass">Password<br>
             <input size="16" type="text" name="empPhoneNumber">PhoneNumber<br>
             <input type="submit" name="addEmp"><br>   
                </form>

    </fieldset>

     </li>


       
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
    displayWorkLoad($empWorker, $empName);
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





