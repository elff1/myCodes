<?php
	session_start();
	
	// get the post variables and using escape character.
	$ISBN=$_POST['ISBN'];
	$name=$_POST['bookName'];
	$type=$_POST['bookType'];
	$publisher=$_POST['publisher'];
	$author=$_POST['author'];
	$year=$_POST['publishYear'];
	$price=$_POST['price'];
	$number=$_POST['number'];	
	if (!get_magic_quotes_gpc()) {
		$ISBN = addslashes($ISBN);
		$author = addslashes($author);
		$name = addslashes($name);
		$type = addslashes($type);
		$publisher = addslashes($publisher);
		$year = intval($year);
		$price = doubleval($price);
		$number = intval($number);
	}
	$ISBN = trim($ISBN);
	$type = trim($type);
	$name = trim($name);
	$publisher = trim($publisher);
	$year = trim($year);
	$author = trim($author);
	$price = trim($price);
	$number = trim($number);
	
	// check the data
	if($price < 0){
		echo "<script language='javascript'>alert('Price is negetive!');history.back();</script>";
		exit;
	}
	if($number <= 0){
		echo "<script language='javascript'>alert('Number should positive!');history.back();</script>";
		exit;
	}
	if($year != "" && ($year < 0 || $year > date('Y'))){
		echo "<script language='javascript'>alert('Publish year is invalid!');history.back();</script>";
		exit;
	}
	
	// connect to the MySQL database
	@ $db = new mysqli('localhost', 'root', '', 'library');
	if (mysqli_connect_errno()) {
		echo 'Error: Could not connect to database. Please try again later.';
		exit;
	}
	
	// search the book first
	$query = "select * from book where ISBN = '".$ISBN."'";
	$result = $db->query($query);
	$row = $result->fetch_assoc();
	if($row){
		// if the book already in the database, check the information correctness
		if($row['name'] != $name){
			echo "<script language='javascript'>
				alert('Book name is wrong, which should be ".$row['name'].".');history.back();</script>";
			exit;
		}
		
		if($type != "")
			if($row['type'] == ""){
				$query = "update book set type = '".$type."' where ISBN = '".$ISBN."'";
				$result = $db->query($query);
				if(!result){
					echo "<script language='javascript'>alert('Update book type error!');history.back();</script>";
					exit;
				}
			}
			else if($row['type'] != $type){
				echo "<script language='javascript'>
					alert('Book type is wrong, which should be ".$row['type'].".');history.back();</script>";
				exit;
			}
		
		if($year != "")
			if($row['year'] == "0"){
				$query = "update book set year = ".$year." where ISBN = '".$ISBN."'";
				$result = $db->query($query);
				if(!result){
					echo "<script language='javascript'>alert('Update book publish year error!');history.back();</script>";
					exit;
				}
			}
			else if($row['year'] != $year){
				echo "<script language='javascript'>
					alert('Publish year is wrong, which should be ".$row['year'].".');history.back();</script>";
				exit;
			}
		
		if($publisher != "")
			if($row['publisher'] == ""){
				$query = "update book set publisher = '".$publisher."' where ISBN = '".$ISBN."'";
				$result = $db->query($query);
				if(!result){
					echo "<script language='javascript'>alert('Update book publisher error!');history.back();</script>";
					exit;
				}
			}
			else if($row['publisher'] != $publisher){
				echo "<script language='javascript'>
					alert('Book publisher is wrong, which should be ".$row['publisher'].".');history.back();</script>";
				exit;
			}
				
		if($author != "")
			if($row['author'] == ""){
				$query = "update book set author = '".$author."' where ISBN = '".$ISBN."'";
				$result = $db->query($query);
				if(!result){
					echo "<script language='javascript'>alert('Update author type error!');history.back();</script>";
					exit;
				}
			}
			else if($row['author'] != $author){
				echo "<script language='javascript'>
					alert('Book author is wrong, which should be ".$row['author'].".');history.back();</script>";
				exit;
			}
		
		if($row['price'] != $price){
			echo "<script type='text/javascript'>
				alert('Book price is wrong, which should be ".$row['price'].".');history.back();</script>";
			exit;
		}
		
		$query = "update book set amount = amount + ".$number.",
			stock = stock + ".$number." where ISBN = '".$ISBN."'";
	}else{
		// if not, insert the books
		$query = "insert into book(ISBN,name,type,year,publisher,author,price,amount,stock)
			values('".$ISBN."','".$name."','".$type."','".$year."','".$publisher."','".$author."','".$price."','".$number."','".$number."')";
	}
	
	// insert information into the database
	$result = $db->query($query);
	if($result){
		echo "<script language='javascript'>alert('Add books successfully!');history.back();</script>";
	}else{
		echo "<script language='javascript'>alert('Add books error!');history.back();</script>";
	}
	
	// close the database
	$db->close();
?>