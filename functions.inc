<?php

date_default_timezone_set("America/Chicago");

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

function display_form_row($system_time, $display_time, $slots=3) {
	$i = 0;
	echo "<p>$display_time - \n";
	while ($i < $slots) {
		echo "<input type='text' name='timeslot' value='$display_time' />\n";
		$i++;
	}
	echo "</p>\n";
}

function display_simple_row($times) {
	echo "Name: <input type='text' name='name' />\n";
	echo "Time: <select name='time'>\n";
	foreach ($times as $key => $value) {
		echo "\t<option value='$key'>$value</option>\n";
	}
	echo "</select>\n";
}

function display_form($lunch_times, $form_name="schedule") {
	$self_post = $_SERVER['PHP_SELF'];
	echo "<form method='post' action='$self_post' name='$form_name'>\n";
	//foreach ($lunch_times as $key => $value) {
	//	display_form_row($key, $value);
	//}
	display_simple_row($lunch_times);
	echo "<input type='submit' name='submit' value='Add' />\n";
	echo "<input type='submit' name='submit' value='Clear' />\n";
	echo "<input type='submit' name='submit' value='View' />\n";
	echo "</form>\n";
}

function append_file($file, $name, $slot) {
	$fh = fopen($file, 'a') or die("Can't open file.");
	fwrite($fh, "$slot,$name\n");
	fclose($fh);
}

function reset_file($file) {
	unlink($file);
	$fh = fopen($file, 'w');
	$timestamp = date('r')."\n";
	fwrite($fh, $timestamp);
	fclose($fh);
}

function read_file($file) {
	$file_array = file($file);
	return $file_array;
}

function display_schedule($file_array) {
	$schedule_reset = $file_array["0"];
	foreach ($file_array as $key => $value) {
		if ($key != 0) {
			$placeholder = explode(",", $value);
			$time = $placeholder["0"];
			$name = $placeholder["1"];
			echo "<p>$name is scheduled for $time.</p>\n";
		}
	}
	echo "<p>Schedule last reset: $schedule_reset</p>\n";
}

?>
