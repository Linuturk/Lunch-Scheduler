<?php

function html_header($page_title) {
	echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";
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
	echo "<p>$display_time - \n";
	while ($i < $slots) {
		echo "<input type='text' name='slot$i-$system_time' />\n";
		$i++;
	}
	echo "</p>\n";
}

function display_schedule($lunch_times, $form_name="schedule") {
	echo "<form action=\"$_SERVER['PHP_SELF']\" name='$form_name'>\n";
	foreach ($lunch_times as $key => $value) {
		display_row($key, $value);
	}
	echo "<input type='submit' />\n";
	echo "</form>\n";
}

?>
