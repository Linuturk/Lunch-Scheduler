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

echo "<h1>lunch.onitato.com</h1>\n";

if (!empty($_POST)) {
	echo "<h1>You can click a button. Good job big boy.</h1>\n";
	display_form($times);
} else {
	display_form($times);
}

html_footer();

?>
