<?php 
	if (isset($_SESSION['admin_id']) && isset($_SESSION['pwd'])){
		// if exists some session, check them
		$id = $_SESSION['admin_id'];
		$password = $_SESSION['pwd'];
		
		// connect to the MySQL database
		@ $db = new mysqli('localhost', 'root', '', 'library');
		if (mysqli_connect_errno()) {
			echo 'Error: Could not connect to database. Please try again later.';
			exit;
		}
		
		// check whether the session is correct
		$query = "select * from administrator where id = '".$id."' and password='".$password."'";
		$result = $db->query($query);
		if ($result->num_rows){
			echo "<script language=javascript>window.location.href='book_query.php';</script>";
		}
		
		// close the database
		$db->close();
	}
?>

<!-- display the header picture -->
<div width="776" align="center">
	<img src="header.jpg"/>
</div>

<!-- create the header -->
<table width="776" border="0" align="center" cellpadding="0" cellspacing="0" class="tableBorder">
<tr>
	<td><a href="index.php">Search</a></td>
</tr>
<tr>
	<td align="right"><a href="login.php">Login</a></td>
</tr>
</table>