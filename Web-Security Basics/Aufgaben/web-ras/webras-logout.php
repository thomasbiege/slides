<?php
require_once "cookie_sql.inc";
require_once "cookie_func.inc";


if(empty($_SERVER['HTTP_REFERER']))
{
	die("Invalid referer-header.");
}

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


# XXX filter parameters
$filterd['uid'] = $tainted['uid'];
$filterd['sid'] = $tainted['sid'];

cookie_session_end($filterd['sid'], $filterd['uid']);

?>
<html>
<head>
<title>Logout Page</title>
</head>
<body>

<?php
	echo "Referer: {$_SERVER['HTTP_REFERER']}<br>";
	echo "<p>Logged Out!<br>UID: <b>{$tainted['uid']}</b><br>Session-ID: <b>{$tainted['sid']}</b>";
?>

</body>
</html>
