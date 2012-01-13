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
		echo "<input type='text' name='slot$i-$system_time' />\n";
		$i++;
	}
	echo "</p>\n";
}

function display_form($lunch_times, $form_name="schedule") {
	$self_post = $_SERVER['PHP_SELF'];
	echo "<form method='post' action='$self_post' name='$form_name'>\n";
	foreach ($lunch_times as $key => $value) {
		display_form_row($key, $value);
	}
	echo "<input type='submit' name='submit' value='Add' />\n";
	echo "<input type='submit' name='submit' value='Clear' />\n";
	echo "<input type='submit' name='submit' value='View' />\n";
	echo "</form>\n";
}

function form_logic($times) {
	if (!empty($_POST)) {
        	$action = $_POST["submit"];
        	if ($action == "Add") {
                	echo "<p>You want to add yourself?</p>\n";
                	display_form($times);
        	} elseif ($action == "Clear") {
                	echo "<p>Clearing the schedule?</p>\n";
                	display_form($times);
        	} elseif ($action == "View") {
                	echo "<p>Want to see the schedule?</p>\n";
                	display_form($times);
        	} else {
                	echo "<h1>HOW DID I GET HERE?!</h1>\n";
        	}
	} else {
        	display_form($times);
	}
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
	echo "<pre>\n";
	print_r($file_array);
	echo "</pre>\n";
}

function display_schedule($file_array) {
	echo $file_array["0"];
	echo "<p>Schedule last reset: $schedule_reset</p>\n";
}

?>
