<?php

error_reporting(E_ALL);
ini_set('display_errors', 1);

$host="localhost"; // Host name
$username=""; // Mysql username
$password=""; // Mysql password
$db_name="test"; // Database name
$tbl_name="members"; // Table name

// Connect to server and select databse.
$link = mysqli_connect("$host", $username, $password, "test");


// Define $myusername and $mypassword
$myusername=$_POST['myusername'];
$mypassword=$_POST['mypassword'];

//$sql="SELECT * FROM $tbl_name WHERE username='$myusername' and password=" . $mypassword;
$stmt = $link->prepare("SELECT * FROM members WHERE username = ? AND password = ?");
$stmt->bind_param("ss", $myusername, $mypassword);
$stmt->execute();

echo "SQL QUERY: " .$sql;
echo "</br> \r\n";

//if (mysqli_multi_query($link, $sql)) {
if ($stmt->fetch()){

	if($result = mysqli_store_result($link)) {

		$count=mysqli_num_rows($result);

		if($count>=1){

			header("location:login_success.php");
		}
		else {
			echo "Wrong Username or Password";
		}
	}

	else {
		echo "Wrong Username or Password";
	}

}
else {
	echo "Table 'members' does not exist";
}

?>


