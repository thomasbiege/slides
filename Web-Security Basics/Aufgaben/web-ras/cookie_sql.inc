<?php

# returns null if an error occurs and first row of record otherwise
function cookie_sql_lookup($db_name, $sqlquery)
{
	$row = array();
	$row = null;

	$db_user = "webras";
	$db_pass = "";
	$db_host = "localhost";


	$db_link  = mysql_connect($db_host, $db_user, $db_pass);
	if(!$db_link)
	{
		echo "<p>Cannot connect: " . mysql_error();
		return null;
	}

	$db_selected = mysql_select_db($db_name);
	if(!$db_selected)
	{
		echo "<p>Cannot use database {$db_name}: " . mysql_error();
		mysql_close($db_link);
		return null;
	}


	$result = mysql_query($sqlquery);
	if(!$result)
	{
		echo "<p>Invalid query: " . mysql_error();
		mysql_close($db_link);
		return null;
	}

	$row = mysql_fetch_array($result);
	/*
	if($row == FALSE)
	{
		echo "<p>Error while fetching rows from database: " . mysql_error();
		mysql_free_result($result);
		mysql_close($db_link);
		return null;
	}
	*/

	mysql_free_result($result);
	mysql_close($db_link);

	return $row;
}

# return 0 on error and 1 otherwise
function cookie_sql_store($db_name, $sqlquery)
{
	$result = false;

	# SQL database handling
	$db_user = "webras";
	$db_pass = "";
	$db_host = "localhost";

	$db_link  = mysql_connect($db_host, $db_user, $db_pass);
	if(!$db_link)
	{
		echo "<p>Could not connect: " . mysql_error();
		return 0;
	}

	$db_selected = mysql_select_db($db_name, $db_link);
	if(!$db_selected)
	{
		echo "<p>Cannot use database {$db_name}: " . mysql_error();
		mysql_close($db_link);
		return 0;
	}

	$result = mysql_query($sqlquery, $db_link);
	if(!$result)
	{
		echo "<p>Invalid query: " . mysql_error();
		mysql_close($db_link);
		return 0;
	}

	mysql_free_result($result);
	mysql_close($db_link);

	return 1;
}

?>
