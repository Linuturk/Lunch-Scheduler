<?php

date_default_timezone_set("America/Chicago");

function database($host, $database, $username, $password) {
	/*
		Simple function to connect to the MySQL database.
		Takes the host, database, username, and password.
	*/
	mysql_connect($host, $username, $password) or die(mysql_error());
	mysql_select_db($database) or die(mysql_error());
}

function html_header($page_title) {
	/*
		Generate the HTML header for the page.
		Pass the page's title as a string.
	*/
	echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";
	echo "<html>\n";
	echo "<head>\n";
	echo "<title>$page_title</title>\n";
	echo "</head>\n";
	echo "<body>\n";
}

function html_footer() {
	/*
		Generate the HTML for the footer.
	*/
	echo "</body>\n";
	echo "</html>";
}

function display_simple_row($times) {
	/*
		Show the HTML inputs to add a name to schedule.
		This takes a specially formatted array to give us the various time slot options.
	*/
	echo "Name: <input type='text' name='name' />\n";
	echo "Time: <select name='time'>\n";
	foreach ($times as $value) {
		echo "\t<option value='$value'>$value</option>\n";
	}
	echo "</select>\n";
}

function display_form($lunch_times, $form_name="form") {
	/*
		Show the entire form.
		Take the lunch slots and the form name as an argument.
		The form name defaults to schedule.
	*/
	$self_post = $_SERVER['PHP_SELF'];
	echo "<form method='post' action='$self_post' name='$form_name'>\n";
	display_simple_row($lunch_times);
	echo "<input type='submit' name='submit' value='Add' />\n";
	echo "<input type='submit' name='submit' value='View' />\n";
	echo "</form>\n";
	echo "<p>Soft limit of 2 per time slot.</p>\n";
}

function add_to_schedule($name, $time) {
	/*
		Take a name and time, sanitize the data, and insert into the database.
	*/
	$name = sanitize($name);
	$query = "INSERT INTO schedule(name, lunchslot, date, timestamp) VALUES('$name', '$time', CURDATE(), NOW())";
	mysql_query($query) or die(mysql_error());
}

function del_from_schedule($id) {
	/*
		Take a specific string, and remove it from the database for the current day.
		This removes all entries from the database, effectively clearing the schedule of that name.
	*/
	$query = "DELETE FROM schedule WHERE date=CURDATE() AND id='$id'";
	mysql_query($query) or die(mysql_error());
}

function show_schedule($lunchslots, $slots=3) {
	/*
		Show the current schedule.
		Takes two arguments:
			- A specially formatted array with the lunch slots you want to show in the schedule.
			- A formatting option for the number of slots the schedule should expect. Defaults to 3.
	*/
	$self_post = $_SERVER['PHP_SELF'];
	echo "<form method='post' action='$self_post' name='schedule'>\n";
	echo "<table border='1'>\n";
	echo "<tr>\n";
	echo "\t<td>Times (CST)</td>\n";
	$i = 0;
	while ($i < $slots) {
		echo "\t<td>&nbsp;</td>\n";
		$i++;
	}
	echo "</tr>\n";
	foreach ($lunchslots as $value) {
		show_lunchslot($value);
	}
	echo "</table>\n";
	echo "<input type='submit' name='submit' value='Remove' />\n";
	echo "</form>\n";
}

function show_lunchslot($slot) {
	/*
		This function pulls the data out of the database for a particular lunch slot, and displays a table
		cell with this information.
		Takes two arguments. One is the slot and the second is the number of slots the system is expecting.
			- The slot is in a pretty format, according to a specially formatted array.
	*/
	$query = "SELECT id, name, lunchslot, date, timestamp FROM schedule WHERE date=CURDATE() AND lunchslot='$slot'";
	$result = mysql_query($query) or die(mysql_error());
	echo "<tr>\n\t<td>$slot</td>\n";
	while ($row = mysql_fetch_array($result)) {
		echo "\t<td><input type='radio' name='clear' value='".$row['id']."'&nbsp;".$row['name']." /></td>\n";
		echo "\t<!-- ".$row['id']." -->\n";
		echo "\t<!-- ".$row['timestamp']." -->\n";
	}
	echo "</tr>\n";
}

function sanitize($string) {
	/*
		Sanitize the input from the user.
		This will strip out anything that could lead to SQL injections.
	*/
	$clean = htmlentities($string);
	$clean = mysql_real_escape_string($clean);
	return $clean;
}

?>
