<?php

require_once("functions.inc");

$db_host = "localhost";
$db_user = "lunch";
$db_pass = "lunchpassword";
$db_database = "lunch";

database($db_host, $db_database, $db_user, $db_pass);

$title="Lunch Schedule";
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
		add_to_schedule($name, $time);
		display_form($times);
		show_schedule();
	} elseif ($action == "Clear") {
		echo "<p>Clearing the schedule.</p>\n";
		display_form($times);
		show_schedule();
	} elseif ($action == "View") {
		echo "<p>Here is the schedule.</p>\n";
		display_form($times);
		show_schedule();
	} else {
		echo "<h1>HOW DID I GET HERE?!</h1>\n";
		display_form($times);
		show_schedule();
	}
} else {
	echo "Let's get started.";
	display_form($times);
	show_schedule();
}

html_footer();

?>
