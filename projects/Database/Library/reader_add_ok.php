<?php
if($_POST[Submit]!=""){
	// get the post variables and using escape character.
	$id=$_POST['id'];
	$name=$_POST['name'];
	$gender=$_POST['gender'];
	$type=$_POST['type'];
	$department=$_POST['department'];
	$enable=$_POST['enable'];
	if (!get_magic_quotes_gpc()) {
		$name = addslashes($name);
		$department = addslashes($department);
		$id = intval($id);
	}
	$id = trim($id);
	$name = trim($name);
	$department = trim($department);
	
	// connect to the MySQL database
	@ $db = new mysqli('localhost', 'root', '', 'library');
	if (mysqli_connect_errno()) {
		echo 'Error: Could not connect to database. Please try again later.';
		exit;
	}
	
	// check whether the reader id has been used
	$sql = "select * from reader where id = ".$id;
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	if($row){
		echo "<script language=javascript>alert('Reader added failed! The ID has been added!');history.back();location.href='reader.php';</script>";
	}
	else{
		// insert the reader information into the database
		$sql="insert into reader(id,name,gender,type,department,number,enable)
			values(".$id.",'".$name."','".$gender."',".$type.",'".$department."',0,".$enable.")";
		$result = $db->query($sql);
		if($result==true){
			echo "<script language=javascript>alert('Reader added successfully!');history.back();location.href='reader.php';</script>";
		}
		else{
			echo "<script language=javascript>alert('Reader added failed!');history.back();window.opener.location.reload();</script>";
		}
	}
	
	// close the database
	$db->close();
}
?>
