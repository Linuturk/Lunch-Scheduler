<?php

date_default_timezone_set("America/Chicago");

function database($host, $database, $username, $password) {
	mysql_connect($host, $username, $password) or die(mysql_error());
	mysql_select_db($database) or die(mysql_error());
}

function html_header($page_title) {
	echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";
	echo "<html>\n";
	echo "<head>\n";
	echo "<title>$page_title</title>\n";
	echo "</head>\n";
	echo "<body>\n";
}

function html_footer() {
	echo "</body>\n";
	echo "</html>";
}

function display_simple_row($times) {
	echo "Name: <input type='text' name='name' />\n";
	echo "Time: <select name='time'>\n";
	foreach ($times as $value) {
		echo "\t<option value='$value'>$value</option>\n";
	}
	echo "</select>\n";
}

function display_form($lunch_times, $form_name="schedule") {
	$self_post = $_SERVER['PHP_SELF'];
	echo "<form method='post' action='$self_post' name='$form_name'>\n";
	display_simple_row($lunch_times);
	echo "<input type='submit' name='submit' value='Add' />\n";
	echo "<input type='submit' name='submit' value='Clear' />\n";
	echo "<input type='submit' name='submit' value='View' />\n";
	echo "</form>\n";
}

function add_to_schedule($name, $time) {
	$query = "INSERT INTO schedule(name, lunchslot, date, timestamp) VALUES('$name', '$time', CURDATE(), NOW())";
	mysql_query($query) or die(mysql_error());
}

function del_from_schedule($name) {
	$query = "DELETE FROM schedule WHERE date=CURDATE() AND name='$name'";
	mysql_query($query) or die(mysql_error());
}

function show_schedule($lunchslots, $slots=3) {
	echo "<table>\n";
	echo "<tr>\n";
	echo "\t<td>Times</td>\n";
	$i = 0;
	while ($i < $slots) {
		echo "\t<td>&nbsp;</td>\n";
	}
	echo "</tr>\n";
	foreach ($lunchslots as $value) {
		show_lunchslot($value);
	}
	echo "</table>\n";
}

function show_lunchslot($slot) {
	$query = "SELECT name, lunchslot, date, timestamp FROM schedule WHERE date=CURDATE() AND lunchslot='$slot'";
	$result = mysql_query($query) or die(mysql_error());
	echo "<tr><td>$slot</td>\n";
	while ($row = mysql_fetch_array($result)) {
		echo "\t<td>".$row['name']."</td>\n";
	}
	echo "</tr>\n";
}

?>
