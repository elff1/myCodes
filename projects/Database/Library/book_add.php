<?php session_start();?>
<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Add Books</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
	<script language="javascript">
	// create a function to check whether information is empty.
	function check(form){
		if(form.ISBN.value==""){
			alert("Please input ISBN!");form.ISBN.focus();return false;
		}
		if(form.bookName.value==""){
			alert("Please input book name!");form.bookName.focus();return false;
		}
		if(form.price.value==""){
			alert("Please input price!");form.price.focus();return false;
		}
		if(form.number.value==""){
			alert("Please input number!");form.number.focus();return false;
		}
		form.submit();
	}
	function checkb(form){
		if(form.userfile.value==""){
			alert("Please select file!");return false;
		}
	}
	</script>
</head>

<body>
<!-- include the page header. -->
<?php include("nav1.php");?>

<!-- create the content form which add one book. -->
<form name="form_add" method="post" action="book_add_ok.php">
	<table width="776" height="432" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td width="173" align="center">ISBN:</td>
			<td width="427" height="39"><input name="ISBN" type="text" id="ISBN"> * </td>
		</tr>
		<tr>
			<td align="center">Book name:</td>
			<td height="39"><input name="bookName" type="text" id="bookName" size="50"> * </td>
		</tr>
		<tr>
			<td align="center">Book type:</td>
			<td><input name="bookType" type="text" id="bookType" size="20"></td>
		</tr>
		<tr>
			<td align="center">Publisher:</td>
			<td><input name="publisher" type="text" id="publisher" size="30"></td>
		</tr>
		<tr>
			<td align="center">Author:</td>
			<td><input name="author" type="text" id="author" size="30"></td>
		</tr>
		<tr>
			<td align="center">Publish year:</td>
			<td><input name="publishYear" type="text" id="publishYear" size="10"></td>
		</tr>
		<tr>
			<td align="center">Price:</td>
			<td><input name="price" type="text" id="price" size="10">(Yuan) * </td>
		</tr>
		<tr>
			<td align="center">Number:</td>
			<td><input name="number" type="text" id="number" size="10"> * </td>
		</tr>
		<tr>
			<td align="center">&nbsp;</td>
			<td><input name="Submit" type="submit" class="btn_grey" value="Add" onClick="return check(form_add)"></td>
		</tr>
	</table>
</form>

<!-- create the content form which batch add books. -->
<form enctype="multipart/form-data" name="form_badd" method="post" action="book_badd_ok.php">
	<table width="776" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td>
				<input type="hidden" name="MAX_FILE_SIZE" value="1000000" />
				<label for="userfile">Select a file:</label>
			</td>
			<td><input type="file" name="userfile" id="userfile"/></td>
		</tr>
		<tr>
			<td></td>
			<td><input type="submit" value="Batch add" onClick="return checkb(form_badd)"/></td>
		</tr>
	</table>
</form>
</body>

<!-- include the page footer. -->
<?php include("footer.php");?>
</html>