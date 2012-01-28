<?php session_start();?>
<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Book Circultate</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
	<script language="jscript">
	// create a function to check whether is empty.
	function check(form){
		if(form.id.value==""){
			alert("Please input reader's ID!");form.id.focus();return false;
		}
		return true;
	}
	</script>
</head>
<body>
	<!-- include the page header. -->
	<?php include("nav1.php");?>
	
	<!-- create the content form. -->
	<form action="" name="temp" method=get>
	<table width="776" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td>Reader ID:</td>
			<td><input name = "id" type = "text" id = "id"></input></td>
		</tr>
		<tr>
			<td><input onclick="window.temp.action='borrow.php';if(check(temp))temp.submit()" type=button value="Borrow books"></td>
			<td><input onclick="window.temp.action='return.php';if(check(temp))temp.submit()" type=button value="Return books"></td>
		</tr>
	</table>
	</form>
	
	<!-- include the page footer. -->
	<?php include("footer.php");?>
</body>
</html>
