<?php
    session_start();
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
?>