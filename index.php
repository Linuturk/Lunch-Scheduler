<?php

require_once("functions.inc");

$title="Lunch Schedule";
$times = array(
	1100 => "11:00 AM",
	1200 => "12:00 PM",
	1300 => "&nbsp;1:00 PM",
	1400 => "&nbsp;2:00 PM",
	1500 => "&nbsp;3:00 PM"
);

html_header($title);
echo "<h1>lunch.onitato.com</h1>\n";
form_logic();
html_footer();

?>
