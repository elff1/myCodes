<?php 
	if (isset($_SESSION['admin_id']) && isset($_SESSION['pwd'])){
		// if exist some sessions, check them
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
		if (!$result->num_rows){
			// if haven't login, jump to the login page
			echo "<script language=javascript>alert('Please login first!');window.location.href='login.php';</script>";
		}
		
		// close the database
		$db->close();
	}
	else{
		echo "<script language=javascript>alert('Please login first!');window.location.href='login.php';</script>";
	}
?>

<!-- display the header picture -->
<div width="776" align="center">
	<img src="header.jpg"/>
</div>

<!-- create the header -->
<table width="776" border="0" align="center" cellpadding="0" cellspacing="0" class="tableBorder">
<tr>
	<td><a href="book_query.php">Search</a></td>
	<td><a href="circulate.php">Borrow/Return</a></td>
	<td><a href="reader.php">Manage Readers</a></td>
	<td><a href="book_add.php">Add Books</a></td>
</tr>
<tr>
	<td></td>
	<td></td>
	<td></td>
	<td align="right">Welcome <?php echo $_SESSION['admin_id'].'!  ';?><a href="logout.php">Logout</a></td>
</tr>
</table>