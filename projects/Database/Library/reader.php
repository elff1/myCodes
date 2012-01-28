<?php session_start();?>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Reader Mananger</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
</head>
<body>
<!-- include the page header. -->
<?php include("nav1.php");?>

<!-- create the reader list table. -->
<table width="776" border="0" align="center" cellpadding="0" cellspacing="0" class="tableBorder">
<tr>
	<td align="center" valign="top">
	<?php
	// connect to the MySQL database
	@ $db = new mysqli('localhost', 'root', '', 'library');
	if (mysqli_connect_errno()) {
		echo 'Error: Could not connect to database. Please try again later.';
		exit;
	}
	
	// search the reader information in the database
	$sql="select * from reader order by id";
	$result = $db->query($sql);
	$info = $result->fetch_assoc();
	if($info==false){
		// no reader
		?>
		<table width="100%" height="30"  border="0" cellpadding="0" cellspacing="0">
			<tr><td height="36" align="center">No reader.</td></tr>
		</table>
		<table width="100%"  border="0" cellspacing="0" cellpadding="0">
			<tr><td><a href="reader_add.php">Add reader</a></td></tr>
		</table>
		<?php 
	}else{
		// list all the readers
		?>
		<table width="100%"  border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td width="87%">&nbsp;</td>
				<td width="13%"><a href="reader_add.php">Add reader</a></td>
			</tr>
		</table>
		<table width="96%"  border="1" cellpadding="0" cellspacing="0" bordercolor="#FFFFFF" bordercolordark="#D2E3E6" bordercolorlight="#FFFFFF">
			<tr align="center" bgcolor="#e3F4F7">
			    <td width="13%">ID</td>
			    <td width="13%">Name</td>
			    <td width="8%">Gender</td>
			    <td width="15%">Type</td>
			    <td width="18%">Department</td>
			    <td width="15%">Borrow number</td>
			    <td width="8%">Enable</td>
			    <td colspan="1">Operate</td>
			</tr>
			<?php
			do{
				?> <tr>
			    <td style="padding:5px;"><?php echo $info['id'];?> </td>  
			    <td style="padding:5px;"><?php echo $info['name'];?> </td>
			    <td align="center">
			    	<?php
			    		switch($info['gender']){
			    			case 'm': echo "Male";break;
			    			case 'f': echo "Female";break;
			    		} 
					?>
				</td>
			    <td style="padding:5px;">
			    	<?php
			    		switch($info['type']){
			    			case 3: echo "Undergraduate";break;
			    			case 1: echo "Gratuate";break;
			    			case 5: echo "Teacher";break;
			    		} 
					?>
			    </td>
			    <td align="left">&nbsp;<?php echo $info['department'];?> </td>
			    <td align="center"><?php echo $info['number'];?> </td>
			    <td align="center">
			    	<?php
			    		switch($info['enable']){
			    			case 1: echo "Yes";break;
			    			case 0: echo "No";break;
			    		} 
					?>
				</td>
			    <td width="11%" align="center"><a href="reader_del.php?id=<?php echo $info[id];?> ">Delete</a></td>
			    </tr>
				<?php 
			}while($info = $result->fetch_assoc());
	}
					// close the database
					$db->close();
				?>
		</table>
	</td>
</tr>
</table>

<!-- include the page footer. -->
<?php include("footer.php");?>
</body>
