<?php
	session_start();
	
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
	$sql = "select * from book where ISBN = '".$isbn."'";
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	
	// the borrow book number of different reader type
	$limit = array(1 => 6, 3 => 3, 5 => 10);
	if(!$row){
		// book not found and return to the borrow page
		echo "<script language=javascript>alert('Book ".$isbn." not found!');window.location.href='borrow.php?id=".$readerid."';</script>";
	}
	else if(!$row['stock']){
		// no more stock of the book and return
		echo "<script language=javascript>alert('Book ".$isbn." no stock!');window.location.href='borrow.php?id=".$readerid."';</script>";
	}
	else{
		// check whether the reader can borrow more books
		$sql="select * from reader where id = ".$readerid;
		$result = $db->query($sql);
		$row = $result->fetch_assoc();
		if($row['number']>=$limit[$row['type']]){
			echo "<script language=javascript>alert('Can not borrow more books!');window.location.href='borrow.php?id=".$readerid."';</script>";
		}
		else{
			// check whether the reader have borrowed this book
			$sql="select * from borrow where readerID = ".$readerid." and ISBN = '".$isbn."' and ifReturn = 0";
			$result = $db->query($sql);
			$row = $result->fetch_assoc();
			if($row){
				echo "<script language=javascript>alert('Can not borrow the same book!');window.location.href='borrow.php?id=".$readerid."';</script>";
			}
			else{
				// start borrow this book
				$sql = "select * from reader where id = ".$readerid;
				$result = $db->query($sql);
				$row = $result->fetch_assoc();
				
				// the borrow time limit of different type readers
				$TimeLimit = array(3 => 30, 1 => 40, 5 => 60);
				$borrowTime=date('Y-m-d');
				// calculate the return time
				$returnTime=date("Y-m-d",(time()+3600*24*$TimeLimit[$row['type']]));
				$operator=$_SESSION['admin_id'];
				$sql = "insert into borrow(readerID,ISBN,borrowTime,returnTime,operator,ifReturn)values('$readerid','$isbn','$borrowTime','$returnTime','$operator',0)";
				$result = $db->query($sql);
				
				$sql = "update reader set number = number + 1 where id = ".$readerid;
				$result = $db->query($sql);
				
				$sql = "update book set stock = stock - 1 where ISBN = '".$isbn."'";
				$result = $db->query($sql);
				
				// display the information and turn to the borrow page
				echo "<script language=javascript>alert('Borrow book ".$isbn." successfully!');window.location.href='borrow.php?id=".$readerid."';</script>";
			}
		}
	}
	
	// close the database
	$db->close();
?>