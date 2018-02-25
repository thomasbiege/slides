<?php
require_once "myrand.inc";
require_once "cookie_sql.inc";
require_once "cookie_func.inc";

$tainted = array();
$filtered = array();
$esc_html = array();
$esc_sql = array();

if(empty($_SERVER['HTTP_REFERER']))
{
	die("Invalid referer-header.");
}

$cookie_ok = cookie_session_verify();

if($cookie_ok == false)
{
	if(!empty($_GET['uid']))
	{
		$tainted['uid'] = $_GET['uid'];
	}
	else
	{
		die("Please specify a user-id.");
	}
	if(!empty($_GET['sid']))
	{
		$tainted['sid'] = $_GET['sid'];
	}
	else
	{
		die("Please specify a session-id.");
	}

	$filterd['uid'] = $tainted['uid'];
	$filterd['sid'] = $tainted['sid'];

	cookie_session_new($filterd['sid'], $filterd['uid']);
}
else
{
	$sqlquery = "SELECT * FROM sess WHERE session_id='{mysql_real_escape_string($_COOKIE['sess_id'])}'";
	$row = cookie_sql_lookup("session_management", $sqlquery);
	if(is_null($row) or $row == false)
	{
	        die("<p><b>An db-lookup error occurred (sess). Good Bye.</br>");
	}
	$sqlquery = "SELECT * FROM users WHERE id='{$row['uid']}'";
	$row = cookie_sql_lookup("accounts", $sqlquery);
	if(is_null($row) or $row == false)
	{
	        die("<p><b>An db-lookup error occurred (acc). Good Bye.</br>");
	}

	# protect against session fix attacks
	$sid_new = myrand();
	cookie_session_update($_COOKIE['sess_id'], $sid_new, $row['id']);

	$tainted['password']  = $row['password'];
	$tainted['loginname'] = $row['loginname'];
	$tainted['uid']       = $row['id'];
	$tainted['sid']       = $sid_new;
}
?>
<html>
<head>
<title>Memebers Page</title>
</head>
<body>

<?php
	echo "Referer: {$_SERVER['HTTP_REFERER']}<br>";
	echo "<p>Welcome!<br>UID: <b>{$tainted['uid']}</b><br>Session-ID: <b>{$tainted['sid']}</b><br>Your authorisation is: <b>Member</b>";
	echo "<p><a href=\"webras-logout.php?uid={$tainted['uid']}&sid={$tainted['sid']}\">Click Here to Logout!</a>";
?>



</body>
</html>
