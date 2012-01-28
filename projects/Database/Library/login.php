<?php session_start();?>
<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Login</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
	<script language="javascript">
	// create a function to check whether the id or password is empty.
	function check(form){
		if(form.id.value==""){
			alert("Please input ID!");form.id.focus();return false;
		}
		if(form.password.value==""){
			alert("Please input password!");form.password.focus();return false;
		}
		form.submit();
	}
</script>
</head>
<body>
	<!-- include the page header. -->
	<?php include("nav0.php");?>
	
	<!-- create the content form. -->
	<form name="form_log" action="login_ok.php" method="post">
	<table width="776" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td>ID:</td>			
			<td><input name="id" type="text" size="20"/></td>
		</tr>
		<tr>
			<td>Password:</td>
			<td><input name="password" type="password" size="20"/></td>
		</tr>
		<tr>
			<td></td>
			<td><input type="submit" name="submit" value="Login" onClick="return check(form_log)"/></td>
		</tr>
	</table>
	</form>
	
	<!-- include the page footer. -->
	<?php include("footer.php");?>
</body>
</html>