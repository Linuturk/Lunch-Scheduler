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
	$query = "INSERT INTO schedule(name, lunchslot, date, timestamp) VALUES('$name', '$time', CURDATE(), CURTIME())";
	echo "<!-- $query -->";
	mysql_query($query) or die(mysql_error());
}

function del_from_schedule($name) {
	mysql_query("DELETE FROM schedule WHERE date=CURDATE() AND name='$name'") or die(mysql_error());
}

function show_schedule() {
	$query = "SELECT name, lunchslot, date, timestamp FROM schedule WHERE date=CURDATE() ORDER BY lunchslot";
	$result = mysql_query($query) or die(mysql_error());
	while ($row = mysql_fetch_array($result)) {
		echo "<p>".$row['name']." - ".$row['lunchslot']." - ".$row['date']."</p>\n";
		echo "<!-- Entered at: ".$row['timestamp']." -->\n";
	}
}

?>
