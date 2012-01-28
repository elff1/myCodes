<?php
	// connect to the MySQL database
	@ $db = new mysqli('localhost', 'root', '', 'library');
	if (mysqli_connect_errno()) {
		echo 'Error: Could not connect to database. Please try again later.';
		exit;
	}
	
	// get the reader's borrow information first
	$id = $_GET[id];
	$sql = "select * from reader where id = ".$id;
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	if($row['number']){
		// some books haven't returned
		echo "<script language=javascript>alert('There are ".$row['number']." books borrowed. Can not delete!');
			window.location.href='reader.php';</script>";
	}
	else{
		// delete the reader
		$sql = "delete from reader where id=".$id;
		$result = $db->query($sql);
		if($sql){
			echo "<script language=javascript>alert('Delete reader successfully!');window.location.href='reader.php';</script>";
		}
		else{
			echo "<script language=javascript>alert('Delete reader failed!');window.location.href='reader.php';</script>";
		}
	}
	
	// close the database
	$db->close();
?>

