<?php

require_once("functions.inc");

$title="Lunch Schedule";
$schedule_file="temp.txt";
$times = array(
	1100 => "11:00 AM",
	1200 => "12:00 PM",
	1300 => "1:00 PM",
	1400 => "2:00 PM",
	1500 => "3:00 PM"
);

html_header($title);
echo "<h1>lunch.onitato.com</h1>\n";

reset_file($schedule_file);
append_file($schedule_file, "John", "slot0");
append_file($schedule_file, "Jane", "slot1");
append_file($schedule_file, "Sam", "slot2");
read_file($schedule_file);

//form_logic($times);
html_footer();

?>
