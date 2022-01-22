<?php
    // Prepare variables for database connection
    $dbusername = "u881042073_ahmed";  // enter database username, I used "arduino" in step 2.2
    $dbpassword = "97198229";  // enter database password, I used "arduinotest" in step 2.2
    $server = "localhost"; // IMPORTANT: if you are using XAMPP enter "localhost", but if you have an online website enter its address, ie."www.yourwebsite.com"
    $My_db = "u881042073_ahmed";
    // Connect to your database
    $dbconnect = mysql_pconnect($server, $dbusername, $dbpassword);
    $dbselect = mysql_select_db("u881042073_ahmed",$dbconnect);
    // Prepare the SQL statement
    $sql = "INSERT INTO SAVE_DATA (Value_1, Value_2) VALUES ('".$_GET["data1"]."','".$_GET["data2"]."')";    
    // Execute SQL statement
    mysql_query($sql);
?>