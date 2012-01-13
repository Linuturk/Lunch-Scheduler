<?php

require_once("functions.inc");

$title="Lunch Schedule";
$schedule_file="/tmp/temp.txt";
$schedule_array = read_file($schedule_file);
$times = array(
	1100 => "11:00 AM",
	1200 => "12:00 PM",
	1300 => "1:00 PM",
	1400 => "2:00 PM",
	1500 => "3:00 PM"
);

html_header($title);

echo "<h1>lunch.onitato.com</h1>\n";

if (!empty($_POST)) {
	$action = $_POST["submit"];
	if ($action == "Add") {
		$name = $_POST["name"];
		$time = $_POST["time"];
		echo "<p>Adding $name to the schedule at $time.</p>\n";
		append_file($schedule_file, $name, $time);
		display_form($times);
	} elseif ($action == "Clear") {
		echo "<p>Clearing the schedule.</p>\n";
		reset_file($schedule_file);
		display_form($times);
	} elseif ($action == "View") {
		echo "<p>Here is the schedule.</p>\n";
		display_schedule($schedule_array);
		display_form($times);
	} else {
		echo "<h1>HOW DID I GET HERE?!</h1>\n";
	}
} else {
	display_schedule($schedule_array);
	display_form($times);
}

html_footer();

?>
