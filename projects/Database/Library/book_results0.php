<?php session_start();?>
<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Book Search</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
</head>
<body>
	<!-- include the page header. -->
	<?php include("nav0.php");?>
	
	<!-- create the result table. -->
	<table width="776" border="0" align="center" cellpadding="0" cellspacing="0">
	<?php
		// get the post variables and using escape character. 
		$searchtype=$_POST['searchtype'];
		$searchterm=trim($_POST['searchterm']);
		if (!get_magic_quotes_gpc()){
			$searchtype = addslashes($searchtype);
			$searchterm = addslashes($searchterm);
		}
		
		// connect to the MySQL database
		@ $db = new mysqli('localhost', 'root', '', 'library');
		if (mysqli_connect_errno()) {
			echo 'Error: Could not connect to database. Please try again later.';
			exit;
		}
		
		// search the books in the database
		$query = "select * from book where ".$searchtype." like '%".$searchterm."%'";
		$result = $db->query($query);
		$num_results = $result->num_rows;
		?><table width="776" border="0" align="center" cellpadding="0" cellspacing="0" class="tableBorder">
			<tr><td><?php if(!$num_results){
				// if no book found
				echo "No book found.";
			?></td></tr><?php 
			}
			else{
				// if some books found, list them out
				echo $num_results." book has been found:";
			?></td></tr>
			<tr><td>
			<table width="96%"  border="1" cellpadding="0" cellspacing="0" bordercolor="#FFFFFF" bordercolordark="#D2E3E6" bordercolorlight="#FFFFFF">
				<tr align="center" bgcolor="#e3F4F7">
				    <td width="5%">No</td>
				    <td width="12%">ISBN</td>
				    <td width="14%">Author</td>
				    <td width="17%">Book Name</td>
				    <td width="20%">Type</td>
				    <td width="12%">Publisher</td>
				    <td width="5%">Year</td>
				    <td width="5%">Price</td>
				    <td width="5%">Amount</td>
				    <td width="5%">Stock</td>
				</tr>
		<?php 
			$no = 0;
			// fetch each result row
			$info = $result->fetch_assoc();
			do{
				$no++;
			?> <tr>
			    <td align="center"><?php echo $no;?> </td>  
			    <td align="center">&nbsp;<?php echo $info['ISBN'];?> </td>
			    <td align="left">&nbsp;<?php echo $info['author'];?> </td>
			    <td align="left">&nbsp;<?php echo $info['name'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['type'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['publisher'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['year'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['price'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['amount'];?> </td>
			    <td align="center">&nbsp;<?php echo $info['stock'];?> </td>
			    </tr>
				<?php 
			}while($info = $result->fetch_assoc());
			}
		$result->free();
		// close the database
		$db->close();
	?>
	</table>
	
	<!-- include the page footer. -->
	<?php include("footer.php");?>
</body>
</html>