<?php
	$tainted = array();

	if(empty($_SERVER['HTTP_REFERER']))
	{
		die("Invalid referer-header.");
	}

	echo "Referer: {$_SERVER['HTTP_REFERER']}<br>";

	if(!empty($_POST['loginname']))
	{
		$tainted['loginname'] = $_POST['loginname'];
	}
	else
	{
		die("Please specify a loginname.");
	}
	if(!empty($_POST['password']))
	{
	        $tainted['password'] = $_POST['password'];
	}
	else
	{
	        die("Please specify a password.");
	}
	if(!empty($_POST['fullname']))
	{
	        $tainted['fullname'] = $_POST['fullname'];
	}
	else
	{
	        die("Please specify a fullname.");
	}

	echo "<p>Creating new User-Account with the following Parameters:<br>";
	echo "- Loginname: {$tainted['loginname']}<br>";
	echo "- Password : {$tainted['password']}<br>";
	echo "- Fullname : {$tainted['fullname']}<br>";


	# SQL database handling
	$db_user = "webras";
	$db_pass = "";
	$db_host = "localhost";
	$db_name = "accounts";

	$db_link  = mysql_connect($db_host, $db_user, $db_pass);
	if(!$db_link)
	{
	        die("Could not connect: " . mysql_error());
	}
	$db_selected = mysql_select_db($db_name);
	if (!$db_selected)
	{
                $msg = "Cannot use database {$db_name}: " . mysql_error();
                mysql_close($db_link);
                die($msg);
	}


	# verify if user already exists
	$sqlquery =	"SELECT COUNT(*) FROM users WHERE loginname = '{$tainted['loginname']}'";
	$result = mysql_query($sqlquery);
	if(!$result)
	{
                mysql_free_result($result);
                $msg = "Invalid query: " . mysql_error();
                mysql_close($db_link);
                die($msg);
	}

	if(mysql_result($result, 0) > 0)
	{
                mysql_free_result($result);
                $msg = "<p>User already exists.";
                mysql_close($db_link);
                die($msg);
	}
	mysql_free_result($result);


	# insert new user record
	$sqlquery =	"INSERT INTO users (loginname, password, fullname, is_admin) 
			 VALUES ('{$tainted['loginname']}', '{$tainted['password']}', '{$tainted['fullname']}', false)";
	$result = mysql_query($sqlquery);
	if(!$result)
	{
		mysql_free_result($result);
		$msg = "Invalid query: " . mysql_error();
		mysql_close($db_link);
		die($msg);
	}
	mysql_free_result($result);


	# done
	mysql_close($db_link);

	echo "<p>Done!";
?>


