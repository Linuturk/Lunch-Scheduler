<?php

require_once("functions.inc");

$title="Lunch Schedule";
$times = array(
	1100 => "11:00 AM",
	1200 => "12:00 PM",
	1300 => "1:00 PM",
	1400 => "2:00 PM",
	1500 => "3:00 PM"
);

html_header($title);
display_schedule($times);
html_footer();

?>
