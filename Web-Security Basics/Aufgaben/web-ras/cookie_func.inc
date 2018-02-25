<?php

function cookie_get_domain($fqdn)
{
	list($host) = explode(".", $fqdn);

	return str_replace($host, "", $fqdn);
}

function cookie_get_path($fqpn)
{
	return dirname($fqpn);
}

function cookie_url_build($script)
{
	$path = cookie_get_path($_SERVER['PHP_SELF']);
	$server = $_SERVER['SERVER_NAME'];
	$scheme = "http://";

	return $scheme . $server . $path . "/" . $script;
}

function cookie_authtoken_gen($sid, $uid)
{
	$pass = "bumbl3b33";
	$key  = md5($pass);
	$sep = ":";

	$authstr = $sid . $sep . $uid;

	$authtok = md5($authstr . $sep . $key);

	return $authtok;
}

function cookie_authtoken_validate($sid, $uid, $cookie_value)
{
	$tok = cookie_authtoken_gen($sid, $uid);

	if(strcmp($tok, $cookie_value))
	{
		return false;
	}
	else
	{
		return true;
	}
}

function cookie_sid_validate($sid, $uid)
{
	$row    = array();
	$esc_sql = array();

	$esc_sql['uid'] = mysql_real_escape_string($uid);
	$esc_sql['sid'] = mysql_real_escape_string($sid);

	if($uid == 0)
	{
		$sqlquery =  "SELECT * FROM sess WHERE session_id='{$esc_sql['sid']}'";
	}
	else
	{
		$sqlquery =  "SELECT * FROM sess WHERE session_id='{$esc_sql['sid']}' AND uid='{$esc_sql['uid']}'";
	}
	$row = cookie_sql_lookup("session_management", $sqlquery);

	if($row == FALSE)
	{
		return true;
	}

	if(!is_null($row))
	{
		echo "<p>Session-ID {$sid} <b>already exists.</b>";
		return false;
	}

	return true;
}

function cookie_session_new($sid, $uid)
{

	$domain    = cookie_get_domain($_SERVER['SERVER_NAME']);
	$path      = cookie_get_path($_SERVER['PHP_SELF']);
	$secure    = false;
	$authtok   = cookie_authtoken_gen($sid, $uid);
	$expire    = 24 * 60 * 60;  # cookie will expire in 24 hs
	$timestamp = time() + $expire;
	$esc_sql   = array();
	$sqlquery  = "";

	# debug
	echo "<p>Cookie will expire at: <b>" . date('Y-m-d H:i:s', $timestamp) . "</b>";

	if(cookie_sid_validate($sid, 0) == false)
	{
		# this is not userfriendly, we have to provide a login prompt.
		die("<p>Session-Cookie is invalid. Good Bye!");
	}


	# escape parameters
	$esc_sql['uid'] = mysql_real_escape_string($uid);
	$esc_sql['sid'] = mysql_real_escape_string($sid);


	# insert session menagement information
	$sqlquery =	"INSERT INTO sess (session_id, uid, timestamp)
			 VALUES ({$esc_sql['sid']}, {$esc_sql['uid']}, $timestamp)";
	if(cookie_sql_store("session_management", $sqlquery) == 0)
	{
		die("<p>Unable to store session information into database.");
	}

	setcookie('sess_id', $sid, $timestamp, $path, $domain, $secure);
	setcookie('sess_authtoken', $authtok, $timestamp, $path, $domain, $secure);
}

function cookie_session_update($sid_old, $sid_new, $uid)
{
	cookie_session_end($sid_old, $uid);
	return cookie_session_new($sid_new, $uid);
}

function cookie_session_verify()
{
	$row = array();
	$cookie_sessid = $cookie_sesstok = false;

	if(!empty($_COOKIE['sess_id']))
	{
		$cookie_sessid  = $_COOKIE['sess_id'];

		if(!empty($_COOKIE['sess_authtoken']))
		{
			$cookie_sesstok = $_COOKIE['sess_authtoken'];
		}
	}
	if(!$cookie_sessid or !$cookie_sesstok)
	{
		echo "<p>Verify: no cookies found.<br>";
		return false;
	}

	$sqlquery = "SELECT * from sess WHERE session_id='{$cookie_sessid}'";
	$row = cookie_sql_lookup("session_management", $sqlquery);
	if($row == FALSE or is_null($row))
	{
		echo "<p>Verify: No db-entry found for session-state.";
		return false;
	}

	# expired?
	if($row['timestamp'] <= time())
	{
	        echo "<p>Verify: Session expired.";
		cookie_session_end($cookie_sessid, $row['uid']);
	        return false;
	}

	# validate auth token
	return cookie_authtoken_validate($cookie_sessid, $row['uid'], $cookie_sesstok);

	return false;
}


function cookie_session_end($sid, $uid)
{
	$esc_sql   = array();
	$domain    = cookie_get_domain($_SERVER['SERVER_NAME']);
	$path      = cookie_get_path($_SERVER['PHP_SELF']);
	$authtok   = "none";
	$secure    = false;
	$expire    = 2 * 24 * 60 * 60;  # 48 hs
	$timestamp = time() - $expire;


        # escape parameters
        $esc_sql['uid'] = mysql_real_escape_string($uid);
        $esc_sql['sid'] = mysql_real_escape_string($sid);


	# set invalid cookies (XXX_ sid = 0?)
	setcookie('sess_id', $sid, $timestamp, $path, $domain, $secure);
	setcookie('sess_authtoken', $authtok, $timestamp, $path, $domain, $secure);


	# delete session menagement information
	$sqlquery = "DELETE FROM sess WHERE session_id='{$esc_sql['sid']}' AND uid='{$esc_sql['uid']}'";
	if(cookie_sql_store("session_management", $sqlquery) == 0)
	{
	        die("<p>Unable to store session information into database.");
	}
}

?>
