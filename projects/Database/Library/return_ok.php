<?php
	// get the post variables and using escape character.
	$isbn = $_POST['isbn'];
	$readerid = $_POST['readerid'];
	if (!get_magic_quotes_gpc()) {
		$isbn = addslashes($isbn);
	}
	$isbn = trim($isbn);
	
	// connect to the MySQL database
	@ $db = new mysqli('localhost', 'root', '', 'library');
	if (mysqli_connect_errno()) {
		echo 'Error: Could not connect to database. Please try again later.';
		exit;
	}
	
	// search the book in the database
	$sql = "select * from borrow where readerID = ".$readerid." and ISBN = '".$isbn."' and ifReturn = 0";
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	if(!$row){
		// the reader didn't borrow this book
		echo "<script language=javascript>alert('Book ".$isbn." has not been borrowed!');window.location.href='return.php?id=".$readerid."';</script>";
	}
	else{
		// return the book
		$sql = "update borrow set ifReturn = 1 where readerID = ".$readerid." and ISBN = '".$isbn."' and ifReturn = 0";
		$result = $db->query($sql);
		
		$sql = "update reader set number = number - 1 where id = ".$readerid;
		$result = $db->query($sql);
		
		$sql = "update book set stock = stock + 1 where ISBN = '".$isbn."'";
		$result = $db->query($sql);
		
		// display the information and back to return page
		echo "<script language=javascript>alert('Book ".$isbn." returned successfully!');window.location.href='return.php?id=".$readerid."';</script>";
	}
	
	// close the database
	$db->close();
?>