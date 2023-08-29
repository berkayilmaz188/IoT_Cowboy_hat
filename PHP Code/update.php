<?php
//180208073 Berkay Salih Yilmaz
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

//JSON array etme
$response = array();

// kullanici gonderisi kontrol etme
if (isset($_GET['id']) && isset($_GET['status'])) {

    $id = $_GET['id'];
    $status= $_GET['status'];


    $filepath = realpath (dirname(__FILE__));
    require_once($filepath."/db_connect.php");

    // Database baglanti
    $db = new DB_CONNECT();

    // SQL update etme id ye gore
    $result = mysql_query("UPDATE led SET status= '$status' WHERE id = '$id'");

    // 
    if ($result) {
        // Basarili yukleme
        $response["success"] = 1;
        $response["message"] = "Veri basariyla yuklendi.";

        // Show JSON response
        echo json_encode($response);
    } else {

    }
} else {
    // Parametre basarisiz
    $response["success"] = 0;
    $response["message"] = "Parameter(s) kayip.Tekrar deneyin";

    // Show JSON response
    echo json_encode($response);
}
?>