<?php

require_once("functions.inc");
require_once("database.inc");

database($db_host, $db_database, $db_user, $db_pass);

$title="Lunch Schedule";
$times = array(
	1000 => "10:00 AM",
	1100 => "11:00 AM",
	1200 => "12:00 PM",
	1300 => "1:00 PM",
	1400 => "2:00 PM",
	1500 => "3:00 PM",
	1600 => "4:00 PM"
);

html_header($title);

echo "<h1>lunch.onitato.com</h1>\n";

if (!empty($_POST)) {
	$action = $_POST["submit"];
	$name = $_POST["name"];
	$time = $_POST["time"];
	if ($action == "Add") {
		if ($name == "" || $name == null) {
			echo "Enter a name, fool!";
		} else {
			echo "<p>Adding $name to the schedule at $time.</p>\n";
			add_to_schedule($name, $time);
		}
	}
	if ($action == "Clear") {
		if ($name == "" || $name == null) {
			echo "Enter a name, fool!";
		} else {
			echo "<p>Clearing $name from today's schedule.</p>\n";
			del_from_schedule($name);
		}
	}
	display_form($times);
	show_schedule($times);
} else {
	display_form($times);
	show_schedule($times);
}

html_footer();

?>
