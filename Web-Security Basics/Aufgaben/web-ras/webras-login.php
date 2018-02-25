<?php
require_once "myrand.inc";
require_once "cookie_sql.inc";
require_once "cookie_func.inc";


$tainted   = array();
$esc_sql   = array();
$esc_html  = array();
$row       = array();
$cookie_ok = false;


$cookie_ok = cookie_session_verify();


# check referer header
if(empty($_SERVER['HTTP_REFERER']))
{
	echo "<p>referer header empty.";
}
else
{
	# XXX also verify URL

	echo "Referer header: {$_SERVER['HTTP_REFERER']}";
}

# check parameters
if($cookie_ok == false)
{
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
}
else
{
	$sqlquery = "SELECT * FROM sess WHERE session_id='{$_COOKIE['sess_id']}'";
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
	$_COOKIE['sess_id'] = $sid_new;

	$tainted['password']  = $row['password'];
	$tainted['loginname'] = $row['loginname'];
}

$esc_sql['loginname'] = mysql_real_escape_string($tainted['loginname']);
$esc_sql['password'] = mysql_real_escape_string($tainted['password']);
$esc_html['loginname'] = htmlentities($tainted['loginname']);
$esc_html['password'] = htmlentities($tainted['password']);


echo "<p>Logging in with the following Credentials:<br>";
echo "- Loginname: '<b>{$esc_html['loginname']}</b>'<br>";
echo "- Password : '<b>{$esc_html['password']}</b>'<br>";


# verify if user exists and pasword is correct
$sqlquery =	"SELECT * FROM users
		WHERE loginname = '{$esc_sql['loginname']}'
		AND password = '{$esc_sql['password']}'";

$row = cookie_sql_lookup("accounts", $sqlquery);
if(is_null($row))
{
	  die("<p><b>Credentials wrong. Good Bye.</br>");
}

# print first record only: no HTML escaping *ouch* 
printf("<p>SQL record: <b>loginname: %s  | password: %s | fullname: %s | is_admin: %s</b><br>",
	$row['loginname'], $row['password'], $row['fullname'],
	$row['is_admin']);

# what privileges
if($row['is_admin'] == 0)
{
	$page = "webras-member.php";
}
else
{
	$page = "webras-admin.php";
}

if($cookie_ok == false)
{
	$sessionid = myrand();
}
else
{
	$sessionid = $_COOKIE['sess_id'];
}

# XXX verify if sid already exists in db


echo "<p>Done! <a href=\"{$page}?uid={$row['id']}&sid={$sessionid}\">Click here to continue...</a>";

?>


