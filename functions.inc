<?php

function html_header($page_title) {
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

function display_row($system_time, $display_time, $slots=3) {
	$i = 0;
	echo "<p>$display_time";
	while ($i < $slots) {
		echo "<input type='text' name='slot$i-$system_time' />\n";
		$i++;
	}
	echo "</p>\n";
}

function display_schedule($lunch_times, $form_name="schedule") {
	echo "<form name='$form_name'>\n";
	foreach ($lunch_times as $key => $value) {
		display_row($key, $value);
	}
	echo "</form>\n";
}

?>
