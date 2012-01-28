<?php
	session_start();
	
	// get the post variables and using escape character.
	$id=$_POST[id];
	$pwd=$_POST[password];
	if (!get_magic_quotes_gpc()) {
		$id = addslashes($id);
		$password = addslashes($password);
	}
	
	// create the cheak class
	class chkinput{
		var $id;
		var $pwd;
		
		// the constructor
		function chkinput($x,$y){
			$this->id=$x;
			$this->pwd=$y;
		}
		
		// the check login function
		function checkinput(){
			// connect to the MySQL database
			@ $db = new mysqli('localhost', 'root', '', 'library');
			if (mysqli_connect_errno()) {
				echo 'Error: Could not connect to database. Please try again later.';
				exit;
			}
			
			// search the id in the database
			$sql = "select * from administrator where id='".$this->id."'";
			$result = $db->query($sql);
			$info = $result->fetch_assoc();
			if($info==false){
				// no such id and turn back
				echo "<script language='javascript'>alert('No such ID!');history.back();</script>";
				exit;
			}
			else if($info["password"] != $this->pwd){
				// the password is error and turn back
				echo "<script>alert('Password error!');history.back();</script>";
				exit;
			}
			else if(!$info["enable"]){
				// the id is forbidden and turn back
				echo "<script>alert('This ID has been forbidden!');history.back();</script>";
			}
			else{
				// login successfully and record the session
				echo "<script>window.location='book_query.php';</script>";
				$_SESSION['admin_id']=$info["id"];
				$_SESSION['pwd']=$info["pwd"];
			}
			// close the database
			$db->close();
		}
	}
	
	// new a check class and call the check function.
    $obj=new chkinput(trim($id),trim($pwd));
    $obj->checkinput();
?>
