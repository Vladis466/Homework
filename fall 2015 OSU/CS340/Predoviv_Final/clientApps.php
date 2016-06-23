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
  //Used for displaying work order history.
  $client = $_SESSION['cliID'];
  $showWerks = $finalDB->query("SELECT * FROM Work
                                INNER JOIN Work_On on Work.WID = Work_On.WID
                                INNER JOIN EMPLOYEES on Work_On.EID = EMPLOYEES.EID 
                                WHERE CID = '$client'
                                ORDER BY DateRequested DESC");
//Used for??
  $showVids = $finalDB->query("SELECT * FROM Documentation 
                                LEFT JOIN Job on Documentation.DocID = Job.DocID 
                                WHERE ClientID = '$client' 
                                ORDER BY DateRecieved DESC");


  //INSERT NEW DOC
  if(isset($_POST["addProj"]))
  {

    $addDoc = $finalDB->prepare("INSERT INTO Documentation (MediaType, Description, Link, clientID) VALUES (?, ?, ?, ?)");
    $addDoc->bind_param("sssi", $MediaType, $Description, $File, $client);
    $Description=$_POST["addDescription"];
    $MediaType=$_POST["addMediaType"];
    $File=$_POST["addFile"];
  //https://drive.google.com/file/d/0Byfufr0utaZsVXFWQ0VSODAzcGs/view?usp=sharing
    $addDoc->execute();
    if ($addDoc == 0)
      die(mysqli_error($finalDB)); 
    else
      echo "Succesfully added record";
    $addDoc->close();
  }









  //INSERT NEW WORK REQUEST
  if(isset($_POST["addWork"]))
  {
    $date = date('Y-m-d H:i:s');
    $workType = $_POST["workType"];
    $addWork = $finalDB->prepare("INSERT INTO Work (DateRequested, WorkType, CID) VALUES (?, ?, ?)");
    $addWork->bind_param("ssi", $date, $workType, $client);
    $addWork->execute();
    if ($addWork == 0)
      die(mysqli_error($finalDB)); 
    else
      echo "Succesfully added record";
    $addWork->close();

//Now we need to get the WORK ID from the job we just inserted
    $getWorkID = $finalDB->query("SELECT WID FROM Work WHERE DateRequested = '$date'");
    $row = $getWorkID->fetch_assoc();
    echo $row['WID'];
    $currWID = $row['WID'];        //THE WORK ID!!! Used for the Specialization
    if ($getWorkID == 0)
      die(mysqli_error($finalDB)); 
    $getWorkID->close();


//Update Job or Service Table depending on choice We allready have the ID!
    $workDescription=$_POST["workDescription"];
    $workType=$_POST["workType"];
    $documentChoice=$_POST["documentChoice"];
    $serviceDateTime=$_POST["serviceDateTime"];

    if ($workType = "Job")
    {
      $addJob = $finalDB->prepare("INSERT INTO Job (WID, JobType, DocID) VALUES (?, ?, ?)"); 
      $addJob->bind_param("iss", $currWID, $workDescription, $documentChoice);
      $addJob->execute();

      if ($addJob == 0)
        die(mysqli_error($finalDB)); 
      $addJob->close();
    }


    if ($workType = "Service")
    {
      $addService = $finalDB->prepare("INSERT INTO Service (WID, ServiceType, ServiceDate) VALUES (?, ?, ?)"); 
      $addService->bind_param("iss", $currWID, $workDescription, $serviceDateTime);
      $addService->execute();
    }
    if ($addService == 0)
      die(mysqli_error($finalDB)); 
    $addService->close();


  }

    





























  //Error Check 
  if ($showVids == 0 || $showWerks == 0)
  {
    die(mysqli_error($finalDB));    
  }
    
  //Display work orders and status for given client
  function displayWerks($showWerks)  
  {
     echo "<br><br><table id='data' class='pure-table' border='1'><tr>
     <th>  Work ID  </th><th>  Date Work was Requested </th>
     <th> Date Completed </th><th> Work Type </th>
     <th> Lead Employee </th><th> Hours Worked </th></tr>";
      // output data of each row
     if ($showWerks->num_rows > 0) {
       while($row = $showWerks->fetch_assoc())
       {      
         echo "<tr class='pure-table-odd'><td id='target' class='normals' >".$row["WID"]."</td>
         <td >".$row["DateRequested"]."</td><td>".$row["CompletionDate"]."</td>
         <td>".$row["WorkType"]."</td><td>".$row["Name"]."</td><td>".$row["HrsWorked"]."</td> 
        </tr>";
      }
      echo "</table>";
      } else {
      echo "No Werk Here";
      }    
  }
  
  //Display documents in system by given client
  function displayTable($showVids)
  {
     echo "<br><br><table id='data' class='pure-table' border='1'><tr>
     <th>  DocID  </th><th>  Date Provided </th>
     <th> Media Type </th><th> Description </th>
     <th>  Associated JobID  </th><th>  File  </th></tr>";
      // output data of each row
     if ($showVids->num_rows > 0) {
       while($row = $showVids->fetch_assoc())
       {      
          
          $link_address = $row["Link"];   
                //echo "<button type='button'>Click Me!</button>";          
               //This works like magic, everything in the right place all on one line.
         echo "<tr class='pure-table-odd'><td id='target' class='normals' >".$row["DocID"]."</td>
         <td >".$row["DateRecieved"]."</td><td>".$row["MediaType"]."</td>
         <td>".$row["Description"]."</td><td>".$row["WID"]."</td>
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
     <div class="page-wrap">   
  <table><tr>
  <td>  
  <div id = "box-form">
    <fieldset>
    <legend>Add a new document:</legend>
        <form class="pure-form" action="clientApps.php" method="post">
             File Link<br><input size="16" type="text" name="addFile" required>
             Media Type<br><input size="16" type="text" name="addMediaType" required>
             Description<br><input size="16" type="text" name="addDescription" required>
             <input type="submit" name="addProj"><br>   
        </form>        
    </fieldset>
  </div>
</td>



<td>
<p>So clients ca see their personal documents and display their work order history.
In order to create a work order for a job, there must be a document attached to it.
This is because for my schema, a job is associated a task that must be completed, while
a service is renting out the translator for a specific amount of time. 

So if you were the client and you wanted a new translation, you would first create a document,
then take the DocID and Request Work with that document.</p>
</td>














<td>
  <div id = "box-form">
    <fieldset>
    <legend>Request Work:</legend>
        <form class="pure-form" action="clientApps.php" method="post">
Work Type<br><select name="workType" required>
               <option value='Job'>Request a Job</option>
               <option value='Service'>Request a Service</option>
             </select>
               Description<br>
               <input type="text" name="workDescription" required>
               ServiceDate(if service)<br>
               <input type="datetime-local" name="serviceDateTime">
             DocID(If Job)<br><select name='documentChoice'>
<?php
        //Dropdown menu
        //Query = server-> query for what you want.
        $allCtgrs = $finalDB->query("SELECT DISTINCT DocID FROM Documentation"); //grab category values, no repeats
        //error checking
        if ($allCtgrs == 0)
          die(mysqli_error($finalDB)); 
        else


        echo "Existing DocID's: <br>";
        //new var = next category in queried list of categories
        while($row = $allCtgrs->fetch_object())
        {            //This is how you iterate through all the options in sum shiz
            echo "<option value='$row->DocID'>Document: " . $row->DocID. "</option>";
        }
        $allCtgrs->free();
        echo "<br>";
?>
</select>




















             <input type="submit" name="addWork"><br>   
        </form>        
    </fieldset>
  </div>
</td>

<div class="pure-menu pure-menu-horizontal">
    <ul class="pure-menu-list">

        <li class="pure-menu-item">
              <form class="pure-form" action="clientApps.php" method="post">
                   <button type="submit" class="pure-button pure-button-primary" name="seeDocs">See Personal Documents</button>   
              </form>
        </li>
        <li class="pure-menu-item">
              <form class="pure-form" action="clientApps.php" method="post">
                   <button type="submit" class="pure-button pure-button-primary" name="seeWerks">Display Work Order History</button>   
              </form>
        </li>
        <li class="pure-menu-item">
            <a class="pure-button pure-button-primary" href="Logout.php">Logout</a> 
        </li> 

    </ul>
</div>

<?php
 
  if (isset($_POST["seeDocs"]))
  {
    displayTable($showVids);
  }
  if (isset($_POST["seeWerks"]))
  {
    displayWerks($showWerks);
  }

$finalDB->close();  
?>





</div>
<!--  <footer class="blog-footer site-footer" >
    <p>Spanish-Services Management System</p>
    <p>
      <a href="#">Back to top</a>
    </p>
  </footer>  -->


    </body>

</html>









