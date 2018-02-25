XXX should not be used

<?php
	$tainted = array();

	if(empty($_SERVER['HTTP_REFERER']))
	{
		die("Invalid referer-header.");
	}

	echo "Referer: {$_SERVER['HTTP_REFERER']}<br>";

	if(!empty($_GET['fullname']))
	{
	        $tainted['fullname'] = $_GET['fullname'];
	}
	else
	{
	        die("Please specify a fullname.");
	}
        if(!empty($_GET['sid']))
        {
                $tainted['sid'] = $_GET['sid'];
        }
        else
        {
                die("Please specify a session-id.");
        }

	echo "<p>Welcome <b>{$tainted['fullname']}</b>. Session-ID: <b>{$tainted['sid']}</b> and your authorisation is: <b>Admin</b>";
?>


