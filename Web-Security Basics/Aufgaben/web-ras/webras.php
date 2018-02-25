<?php
require_once 'cookie_sql.inc';
require_once 'cookie_func.inc';

$cookie_ok = cookie_session_verify();

if($cookie_ok)
{
	$url = cookie_url_build("webras-login.php");
	echo "<p>going to: ". $url;
	header("Location: {$url}");
}
?>


<html>
<head>
<title>Web-RAS: Login</title>
</head>
		
<body>

<h1>Please login.</h1>
<p>
<form action="webras-login.php" method="post">
	Loginname: <input type="text" name="loginname" /> <br>
	Password : <input type="password" name="password" />  <br>
	<input type="submit" value="Log me in!"/>
</form>

</body>
</html>
