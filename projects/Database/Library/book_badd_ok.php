<?php session_start();?>
<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Batch Book Add</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
</head>
<body>
<!-- include the page header. -->
<?php include("nav1.php");?>
<?php
	// create a function insert one book list
	function insert($ISBN,$type,$name,$publisher,$year,$author,$price,$number){
		if($ISBN == "" || $name == "" || $price == "" || $number == ""
			|| $price < 0 || $number <= 0 || ($year != "" && ($year < 0 || $year > date('Y'))))
			return false;
		
		// connect to the MySQL database
		@ $db = new mysqli('localhost', 'root', '', 'library');
		if (mysqli_connect_errno()) {
			echo 'Error: Could not connect to database. Please try again later.';
			exit;
		}
		
		// search the book in the database
		$query = "select * from book where ISBN = '".$ISBN."'";
		$result = $db->query($query);
		$row = $result->fetch_assoc();
		if($row){
			// if the book already in the database, check the information correctness
			if($row['name'] != $name){
				return false;
			}
			
			if($type != "")
				if($row['type'] == ""){
					$query = "update book set type = '".$type."' where ISBN = '".$ISBN."'";
					$result = $db->query($query);
					if(!result){
						return false;
					}
				}
				else if($row['type'] != $type){
					return false;
				}
			
			if($year != "")
				if($row['year'] == "0"){
					$query = "update book set year = ".$year." where ISBN = '".$ISBN."'";
					$result = $db->query($query);
					if(!result){
						return false;
					}
				}
				else if($row['year'] != $year){
					return false;
				}
			
			if($publisher != "")
				if($row['publisher'] == ""){
					$query = "update book set publisher = '".$publisher."' where ISBN = '".$ISBN."'";
					$result = $db->query($query);
					if(!result){
						return false;
					}
				}
				else if($row['publisher'] != $publisher){
					return false;
				}
					
			if($author != "")
				if($row['author'] == ""){
					$query = "update book set author = '".$author."' where ISBN = '".$ISBN."'";
					$result = $db->query($query);
					if(!result){
						return false;
					}
				}
				else if($row['author'] != $author){
					return false;
				}
			
			if($row['price'] != $price){
				return false;
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
		if(!$result){
			return false;
		}
		
		// close the database
		$db->close();
		return true;
	}
	
	if ($_FILES['userfile']['error'] > 0){
		// if upload file failed, display the error information
		echo 'Problem: ';
		switch ($_FILES['userfile']['error']){
			case 1: echo 'File exceeded upload_max_filesize';
			break;
			case 2: echo 'File exceeded max_file_size';
			break;
			case 3: echo 'File only partially uploaded';
			break;
			case 4: echo 'No file uploaded';
			break;
			case 6: echo 'Cannot upload file: No temp directory specified';
			break;
			case 7: echo 'Upload failed: Cannot write to disk';
			break;
		}
		exit;
	}
	
	// check the file's type
	if ($_FILES['userfile']['type'] != 'text/plain'){
		echo 'Problem: file is not plain text';
		exit;
	}
	if (!is_uploaded_file($_FILES['userfile']['tmp_name'])){
		echo 'Problem: Possible file upload attack. Filename: ';
		echo $_FILES['userfile']['name'];
		exit;
	}
	
	// read the file
	$fname = $_FILES['userfile']['tmp_name'];
	$handle = @fopen($fname,'r');
	if(!$handle){
		echo "Open file error!<br />";
	}
	else{
		$nums = $numf = 0;
		
		// for each book list, call the insertion functioin
		while (!feof($handle)){
			$buffer = fgets($handle, 4096);
			list($ISBN,$type,$name,$publisher,$year,$author,$price,$number) = explode(",",$buffer);
			$ISBN = trim($ISBN);
			$type = trim($type);
			$name = trim($name);
			$publisher = trim($publisher);
			$year = trim($year);
			$author = trim($author);
			$price = trim($price);
			$number = trim($number);
			$data = array($ISBN,$author,$name,$type,$publisher,$year,$price,$number);
			
			if(insert($ISBN,$type,$name,$publisher,$year,$author,$price,$number)){
				// if insert successfully, record the successful information
				$lists[$nums] = $data;
				$nums++;
			}
			else{
				// if insert failed, record the failed information
				$listf[$numf] = $data;
				$numf++;
			}
		}
		
		// list all the books which inserted successfully
		?><table width="776" border="0" align="center" cellpadding="0" cellspacing="0" class="tableBorder">
			<tr><td><?php echo $nums." book lists added successfully:";?></td></tr>
		<?php if($nums){?>
			<tr><td>
			<table width="96%"  border="1" cellpadding="0" cellspacing="0" bordercolor="#FFFFFF" bordercolordark="#D2E3E6" bordercolorlight="#FFFFFF">
				<tr align="center" bgcolor="#e3F4F7">
				    <td width="6%">No</td>
				    <td width="12%">ISBN</td>
				    <td width="14%">Author</td>
				    <td width="15%">Book Name</td>
				    <td width="20%">Type</td>
				    <td width="12%">Publisher</td>
				    <td width="7%">Year</td>
				    <td width="7%">Price</td>
				    <td width="7%">Number</td>
				</tr>
		<?php 
			$no = 0;
			reset($lists); // Remember this is used to point to the beginning
			$data = current($lists);
			while ($data) {
				$no++;
		?>		<tr>
				    <td align="center"><?php echo $no;?> </td>
					<?php for($i = 0; $i < 8; $i++){
						echo "<td align=\"center\">".$data[$i]."</td>";
					}?>
				</tr>
		<?php
				$data = next($lists);
			}
		}
		
		// list the books inserted failed
		?><table width="776" border="0" align="center" cellpadding="0" cellspacing="0" class="tableBorder">
			<tr><td><?php echo $numf." book lists added failed:";?></td></tr>
		<?php if($numf){?>
			<tr><td>
			<table width="96%"  border="1" cellpadding="0" cellspacing="0" bordercolor="#FFFFFF" bordercolordark="#D2E3E6" bordercolorlight="#FFFFFF">
				<tr align="center" bgcolor="#e3F4F7">
				    <td width="6%">No</td>
				    <td width="12%">ISBN</td>
				    <td width="14%">Author</td>
				    <td width="15%">Book Name</td>
				    <td width="20%">Type</td>
				    <td width="12%">Publisher</td>
				    <td width="7%">Year</td>
				    <td width="7%">Price</td>
				    <td width="7%">Number</td>
				</tr>
		<?php 
			$no = 0;
			reset($listf); // Remember this is used to point to the beginning
			$data = current($listf);
			while ($data) {
				$no++;
		?>		<tr>
				    <td align="center"><?php echo $no;?> </td>
					<?php for($i = 0; $i < 8; $i++){
						echo "<td align=\"center\">".$data[$i]."</td>";
					}?>
				</tr>
		<?php
				$data = next($listf);
			}
		}
	}
		?>		</table>
		</td></tr></table>
		<?php fclose($handle);?>
		
<!-- include the page footer. -->
<?php include("footer.php");?>
</body>
</html>