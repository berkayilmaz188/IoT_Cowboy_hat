<?php
// 180208073 Berkay Salih Yilmaz
class DB_CONNECT {

    // Constructor
    function __construct() {
        
        $this->connect();
    }

    // Destructor
    function __destruct() {
        
        $this->close();
    }

    
    function connect() {

        $filepath = realpath (dirname(__FILE__));

        require_once($filepath."/dbconfig.php");

        // Connecting to  mysql (phpmyadmin) 
        $con = mysql_connect(DB_SERVER, DB_USER, DB_PASSWORD) or die(mysql_error());

        // Select database
        $db = mysql_select_db(DB_DATABASE) or die(mysql_error()) or die(mysql_error());

        // returing connection cursor
        return $con;
    }

    // Database kapatma fonksiyonu
    function close() {
        // Database baglantisi kapatma
        mysql_close();
    }

}

?>