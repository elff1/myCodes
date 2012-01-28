<?php session_start();?>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Book Return</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
	<script language="jscript">
	// create a function to check whether ISBN is empty.
	function check(form){
		if(form.isbn.value==""){
			alert("Please input the book ISBN!");form.isbn.focus();return false;
		}
	}
	</script>
</head>
<body>
<!-- include the page header. -->
<?php include("nav1.php");?>

<!-- create the content form. -->
<form name="form1" method="post" action="return_ok.php">
<table width="776" border="0" align="center" cellpadding="0" cellspacing="0">
<tr>
	<td align="center" valign="top">
	<?php
		// get the post variables and using escape character.
		$id = $_GET['id'];
		if (!get_magic_quotes_gpc()) {
			$id = intval($id);
		}
		$id = trim($id);
		$limit = array(1 => 6, 3 => 3, 5 => 10);
		
		// connect to the MySQL database
		@ $db = new mysqli('localhost', 'root', '', 'library');
		if (mysqli_connect_errno()) {
			echo 'Error: Could not connect to database. Please try again later.';
			exit;
		}
		
		// get the information of the reader id from the database
		$sql = "select * from reader where id = ".$id;
		$result = $db->query($sql);
		$info = $result->fetch_assoc();
		
		if(!$info){
			echo "<script language=javascript>alert('No this reader ID!');history.back();</script>";
			exit;
		}
		else if(!$info['enable']){
			echo "<script language=javascript>alert('This reader is forbidden!');history.back();</script>";
			exit;
		}
	?>
	
	<!-- display the reader's information -->
	<table width="96%" border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td height="27" width=13% align="center">ID:</td>
			<td width=20%><input name="readerid" type="text" id="readerid" value="<?php echo $id;?>"></td>
			<td width=14%>Name:</td>
			<td width=20%><input name="readername" type="text" id="readername" value="<?php echo $info['name'];?>"></td>
			<td width=13%>Gender:</td>
			<td width=20%>
				<input name="readergender" type="text" id="readergender" value="<?php
			    		switch($info['gender']){
			    			case 'm': echo "Male";break;
			    			case 'f': echo "Female";break;
			    		} 
					?>">
			</td>
		</tr>
		<tr>
			<td height="27" width=13% align="center">Department:</td>
			<td width=20%><input name="readerdepartment" type="text" id="readerdepartment" value="<?php echo $info['department'];?>"></td>
			<td width=14%>Type:</td>
			<td width=20%>
				<input name="readertype" type="text" id="readertype" value="<?php
			    		switch($info['type']){
			    			case 3: echo "Undergraduate";break;
			    			case 1: echo "Gratuate";break;
			    			case 5: echo "Teacher";break;
			    		} 
					?>">
			</td>
			<td width=13%>Limit:</td>
			<td width=20%><input name="readerlimit" type="text" id="readerlimit" value="<?php echo $limit[$info['type']];?>"></td>
		</tr>
		<tr>
			<td></td>
			<td align="center" height="39">Book ISBN:</td>
			<td></td>
			<td align="left">
				<input name="readerid" type="hidden" id="readerid" value="<?php echo $info['id'];?>">
				<input name="isbn" type="text" id="isbn">*
			</td>
			<td></td>
			<td align="left">
				<input name="Submit" type="submit" class="btn_grey" value="Return" onClick="return check(form1)">
			</td>
		</tr>
	</table>

	<!-- list the books the reader borrowed -->
	<?php
	$sql="select * from borrow natural join book where readerID = '".$id."' and ifReturn = 0 order by returnTime";
	$result = $db->query($sql);
	$info = $result->fetch_assoc();
	if($info==false){
		?>
		<table width="100%" height="30"  border="0" cellpadding="0" cellspacing="0">
			<tr><td height="36" align="center">No books borrowed.</td></tr>
		</table>
		<?php 
	}else{
		?>
		<table width="96%"  border="1" cellpadding="0" cellspacing="0" bordercolor="#FFFFFF" bordercolordark="#D2E3E6" bordercolorlight="#FFFFFF">
			<tr align="center" bgcolor="#e3F4F7">
			    <td width="8%">No</td>
			    <td width="12%">ISBN</td>
			    <td width="14%">Author</td>
			    <td width="20%">Book Name</td>
			    <td width="8%">Year</td>
			    <td width="15%">Borrow Time</td>
			    <td width="15%">Return Time</td>
			    <td width="8%">Operator</td>
			</tr>
			<?php
			$no = 0;
			do{
				$no++;
				?> <tr>
			    <td align="center"><?php echo $no;?> </td>  
			    <td align="center">&nbsp;<?php echo $info['ISBN'];?> </td>
			    <td align="left">&nbsp;<?php echo $info['author'];?> </td>
			    <td align="left">&nbsp;<?php echo $info['name'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['year'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['borrowTime'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['returnTime'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['operator'];?> </td>
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
</form>
<!-- include the page footer. -->
<?php include("footer.php");?>
</body>
