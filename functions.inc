<?php

date_default_timezone_set("America/Chicago");

function database($host, $database, $username, $password) {
        /*
                Simple function to connect to the MySQL database.
                Takes the host, database, username, and password.
        */
        mysql_connect($host, $username, $password) or die(mysql_error());
        mysql_select_db($database) or die(mysql_error());
}

function html_header($page_title) {
        /*
                Generate the HTML header for the page.
                Pass the page's title as a string.
        */
        echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";
        echo "<html>\n";
        echo "<head>\n";
        echo "<title>$page_title</title>\n";
        echo "<link rel='stylesheet' type='text/css' href='style.css' />\n";
        echo "<meta http-equiv='refresh' content='60' url='http://lunch.cldsrvr.com/' >\n";
        echo "</head>\n";
        echo "<body>\n";
}

function html_footer() {
        /*
                Generate the HTML for the footer.
        */
        echo "<p class='center'>Maintained by <a href='mailto:linuturk@onitato.com'>Justin Phelps</a> - <a href='https://github.com/Linuturk/Lunch-Scheduler/issues' target='_blank'>Report Issues</a></p>\n";
        echo "</body>\n";
        echo "</html>";
}

function add_to_schedule($name, $time) {
        /*
                Take a name and time, sanitize the data, and insert into the database.
        */
        $name = sanitize($name);
        $query = "INSERT INTO schedule(name, lunchslot, date, timestamp) VALUES('$name', '$time', CURDATE(), NOW())";
        mysql_query($query) or die(mysql_error());
}

function del_from_schedule($id) {
        /*
                Take a specific string, and remove it from the database for the current day.
                This removes all entries from the database, effectively clearing the schedule of that name.
        */
        $query = "DELETE FROM schedule WHERE date=CURDATE() AND id='$id'";
        mysql_query($query) or die(mysql_error());
}

function show_schedule($lunchslots, $slots=4) {
        /*
                Show the current schedule.
                Takes two arguments:
                        - A specially formatted array with the lunch slots you want to show in the schedule.
                        - A formatting option for the number of slots the schedule should expect. Defaults to 3.
        */
        $self_post = $_SERVER['PHP_SELF'];
        echo "<form method='post' action='$self_post' name='schedule'>\n";
        echo "<table class='center'>\n";
        echo "<tr>\n";
        echo "\t<td class='label'>Times (CST)</td>\n";
        echo "\t<td><input id='name' type='text' name='name' /></td>\n";
        echo "\t<td><select name='time'>\n";
        foreach ($lunchslots as $value) {
                echo "\t\t<option value='$value'>$value</option>\n";
        }
        echo "\t</select></td>\n";
        echo "\t<td class='center'><input type='submit' name='submit' value='Add' /></td>\n";
        echo "</tr>\n";
        foreach ($lunchslots as $value) {
                show_lunchslot($value, $slots);
        }
        echo "</table>\n";
        echo "<p class='center'>\n";
        echo "<input id='submit' type='submit' name='submit' value='Remove' />\n";
        echo "<input id='submit' type='submit' name='submit' value='Refresh' />\n";
        echo "</p>\n";
        echo "</form>\n";
}

function show_lunchslot($slot, $slots) {
        /*
                This function pulls the data out of the database for a particular lunch slot, and displays a table
                cell with this information.
                Takes two arguments. One is the slot and the second is the number of slots the system is expecting.
                        - The slot is in a pretty format, according to a specially formatted array.
                        - Slots controls how many table columns are expected.
        */
        $query = "SELECT id, name, lunchslot, date, timestamp FROM schedule WHERE date=CURDATE() AND lunchslot='$slot'";
        $result = mysql_query($query) or die(mysql_error());
        $num_rows = mysql_num_rows($result);
        echo "<tr>\n\t<td class='label'>$slot</td>\n";
        while ($row = mysql_fetch_array($result)) {
                echo "\t<td class='data'><input type='radio' name='clear' value='".$row['id']."' />&nbsp;".unsanitize($row['name'])."</td>\n";
                echo "\t<!-- ".$row['id']." -->\n";
                echo "\t<!-- ".$row['timestamp']." -->\n";
        }
        while ($num_rows < $slots) {
                echo "\t<td class='data'>&nbsp;</td>\n";
                $num_rows++;
        }
        echo "</tr>\n";
}

function sanitize($string) {
        /*
                Sanitize the input from the user.
                This will strip out anything that could lead to SQL injections.
        */
        $clean = htmlentities($string);
        $clean = mysql_real_escape_string($clean);
        return $clean;
}

function unsanitize($string) {
        /*
                Make the string suitable for display to the user.
                This effectively reverses the sanitize function.
        */
        $dirty = stripslashes($string);
        $dirty = html_entity_decode($dirty);
        return $dirty;
}

?>
