<?php
  if(isset($_POST['gonder2'])) {
    $v1 = $_POST['gonder1'];


    $id = 1 ;
    $status= $_POST['gonder1'];


    // Include data base connect class
    $filepath = realpath (dirname(__FILE__));
    require_once($filepath."/db_connect.php");

    // Connecting to database
    $db = new DB_CONNECT();

    // Fire SQL query to update Matrix led string data
    $result = mysql_query("UPDATE led SET status= '$status' WHERE id = '$id'");

    $page = file_get_contents('http://www.berkayilmazkou.site/inbox.html');
    echo $page;
}
?>
