<?php

// Import the necessary functions and database setting.
require_once("functions.inc");
require_once("database.inc");

// Connect to the database.
database($db_host, $db_database, $db_user, $db_pass);

// Set the page title, and the available time slots.
$title="Lunch Schedule";
$times = array(
    "0000" => "12:00 AM",
    "0100" => "1:00 AM",
    "0200" => "2:00 AM",
    "0300" => "3:00 AM",
    "0400" => "4:00 AM",
    "0500" => "5:00 AM",
    "0600" => "6:00 AM",
    "0700" => "7:00 AM",
    "0800" => "8:00 AM",
    "0900" => "9:00 AM",
    "1000" => "10:00 AM",
    "1100" => "11:00 AM",
    "1200" => "12:00 PM",
    "1300" => "1:00 PM",
    "1400" => "2:00 PM",
    "1500" => "3:00 PM",
    "1600" => "4:00 PM",
    "1700" => "5:00 PM",
    "1800" => "6:00 PM",
    "1900" => "7:00 PM",
    "2000" => "8:00 PM",
    "2100" => "9:00 PM",
    "2200" => "10:00 PM",
    "2300" => "11:00 PM"
);

// Display the HTML headers.
html_header($title);

// Big title to the page.
$page_title = $_SERVER['HTTP_HOST'];
echo "<h1>$page_title</h1>\n";

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
			echo "<p class='center'>Enter a name, fool!</p>\n";
		} else {
			// Add to the database.
			$name = sanitize($name);
			add_to_schedule($name, $time);
		}
	} elseif ($action == "Remove") {
		// Clear from the database for the current day.
		$id = $_POST["clear"];
		del_from_schedule($id);
		}
}

show_schedule($times);

//echo "<p class='center'>3 per time slot please.</p>\n";

// Vendor Schedule
require_once('vendor.inc');

// Close out the HTML.
html_footer();

?>
