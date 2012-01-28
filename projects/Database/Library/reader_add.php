<?php session_start();?>
<html>
<head>
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8" />
	<title>Add Reader</title>
	<meta http-equiv="Content-Language" content="en-us" />	
	<meta http-equiv="imagetoolbar" content="no" />
	<script language="jscript">
	// create a function to check whether the reader id and name is empty.
	function check(form){
		if(form.id.value==""){
			alert("Please input ID!");form.id.focus();return false;
		}
		if(form.name.value==""){
			alert("Please input name!");form.name.focus();return false;
		}
	}
	</script>
</head>
<body>
<!-- include the page header. -->
<?php include("nav1.php");?>

<!-- create the content form. -->
<form name="form1" method="post" action="reader_add_ok.php">
	<table width="776" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
		<td width="30%" align="left">ID:</td>
		<td width="70%" height="39"><input name="id" type="text" id="id">* </td>
	</tr>
	<tr>
		<td>Name:</td>
		<td><input name="name" type="text">* </td>
	</tr>
	<tr>
		<td>Gender:</td>
		<td height="35">
			Male:<input type="radio" checked="checked" name="gender" value="m">
			Female:<input type="radio" name="gender" value="f">
		</td>
	</tr>
	<tr>
		<td>Reader type</td>
		<td>
			<select name="type">
				<option value="3">Undergraduate</option>
				<option value="1">Gratuate</option>
				<option value="5">Teacher</option>
			</select>
		</td>
	</tr>
	<tr>
		<td>Department:</td>
		<td><input name="department" type="text" id="department"></td>
	</tr>
	<tr>
		<td>Enable:</td>
        <td>
	        Yes:<input type="radio" checked="checked" name="enable" value="1">
			No:<input type="radio" name="enable" value="0">
		</td>
	</tr>
	<tr>
		<td align="center">&nbsp;</td>
		<td><input name="Submit" type="submit" class="btn_grey" value="Add" onClick="return check(form1)">
	</tr>
    </table>
</form>

<!-- include the page footer. -->
<?php include("footer.php");?>
</body>
</html>
