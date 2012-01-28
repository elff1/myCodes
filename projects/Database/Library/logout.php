<?php
session_start();
// empty the session information
$_SESSION = array();
// destroy the session
session_destroy();
// display the information and turn to the index page
echo "<script language=javascript>alert('Logout successfully');window.location.href='index.php';</script>";
?>