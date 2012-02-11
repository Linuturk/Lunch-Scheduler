<?php

// Import the necessary functions and database setting.
require_once("functions.inc");
require_once("database.inc");

// Connect to the database.
database($db_host, $db_database, $db_user, $db_pass);

// Set the page title, and the available time slots.
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

// Display the HTML headers.
html_header($title);

// Big title to the page.
echo "<h1>lunch.cldsrvr.com</h1>\n";

// If the page hasn't been posted . . . 
if (!empty($_POST)) {
	// Pull the values from POST
	$action = $_POST["submit"];
	$name = $_POST["name"];
	$time = $_POST["time"];
	// If we are adding someone to the schedule . . . 
	if ($action == "Add") {
		// Make sure they entered something.
		if ($name == "" || $name == null) {
			echo "Enter a name, fool!";
		} else {
			// Add to the database.
			$name = sanitize($name);
			echo "<p>Adding $name to the schedule at $time.</p>\n";
			add_to_schedule($name, $time);
		}
	}
	// If we are clearing someone from the schedule . . . 
	if ($action == "Clear") {
		// Make sure they entered something.
		if ($name == "" || $name == null) {
			echo "Enter a name, fool!";
		} else {
			// Clear from the database for the current day.
			echo "<p>Clearing $name from today's schedule.</p>\n";
			del_from_schedule($name);
		}
	}
	// No matter what, show the form and schedule.
	display_form($times);
	show_schedule($times);
// If the page hasn't been posted yet . . . 
} else {
	display_form($times);
	show_schedule($times);
}

// Close out the HTML.
html_footer();

?>
