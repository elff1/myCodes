<?php session_start();?>
<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Book search</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
	<script language="jscript">
	// create a function to check whether search term is empty.
	function check(form){
		if(form.searchterm.value==""){
			alert("Please input search details!");form.searchterm.focus();return false;
		}
		return true;
	}
	</script>
</head>
<body>
	<!-- include the page header. -->
	<?php include("nav1.php");?>
	
	<!-- create the content form. -->
	<form name="form_query" action="book_results.php" method="post">
	<table width="776" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td>Choose Search Type:</td>
			<td><select name="searchtype">
				<option value="name">Name</option>
				<option value="author">Author</option>
				<option value="ISBN">ISBN</option>
				<option value="type">Type</option>
				<option value="publisher">Publisher</option>
				<option value="year">Year</option>
				<option value="price">Price</option>
			</select></td>
		</tr>
		<tr>
			<td>Enter Search Term:</td>
			<td><input name="searchterm" type="text" size="40"/></td>
		</tr>
		<tr>
			<td></td>
			<td><input type="submit" name="submit" value="Search" onClick="return check(form_query)"/></td>
		</tr>
	</table>
	</form>
	
	<!-- include the page footer. -->
	<?php include("footer.php");?>
</body>
</html>