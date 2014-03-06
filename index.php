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
$roles = array(
    "other" => "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAAAAAA6fptVAAAACklEQVQIHWP4BwABAAD/79dRFgAAAABJRU5ErkJggg=="
    ,"alerts" => "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAACA0lEQVQ4jZ2NXUhTcRiH/5GDkEFdJV20TGcndbhznG47bsEiFhG0i0gqgu6iCCLtJkQvTOiLgrrISdRsOCswzIZGtEKLPkSCIKVuo6CLrMx9tY9z3NNFtRy2UF94Lt4f7/N7hSgy8Z66tVqoSdP61czMVdvqYndFR7vlHuNlC7w4ntP7nLeXJCe6ZTkbcum864LJk2SDqpburjcvuiBzw/mRx7vh4dbf+MgEHG8WJf/oUfZp/W6NqXYavV4avV6YbEMLNmmpK8q2/8rvO8tXpfwNUZ7shTEfiseD4vHA+EGI+Ej5bdMDzWJl0YJ0d/15va8py8QhGHZRq6pYVBWGXfDqKNmgM5O4JLf8U06erl6XvCwnGd0DI1sgrFKlKFTJCoRViHjh0S4SF+pi3zvL1ywsuGgd0UJOnVEfDDlgyIFJktiwWcrvPG0mG2jMJs5YrhfIs51SQ/ycJU5kJ9x1wKAdBu2UmdZTZjLld+6p8GA7sVPVsS9tFZv++CviXTVv9ZAdwm640/CX5/t/MT+770ELKLlou/RMCCFEtF06ED9bO0vYTa7XCgO2PKVGI6VGY0GW67VC2E20Q5r91lq5Q8Q6pM+5mzbmrlnR/ZYCSgwGSgyGBflcQEYPKsycMH8Q0TYpPf/DUvh6rDIlPrWaX08drmE5TB/ZOC6EEBVCCOcyqfgJA7CnWuEXZlIAAAAASUVORK5CYII="
    ,"chat" => "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAABQklEQVQ4jZ2SsYrCQBiE52l8lLxCIGhhYRobGwvBKu9wjRACKbSIjRDPRjzBzvaa69zY2W7uiImJc4WbYM5V725g+P9dmIH9WAAAhhv+yloNN4zinM8UxfmdkuHmabiUvmCwpswKyqxgnJ4ZZxfL9ExZzYJxWhCDN01Bf8mdPHEncwqZq3miUOfybidPRH+pKegtuD2k3B4yNcs9u9nRe9VA7c7orPYMxZHzKGEoEobiyFAknCuHIqGz2hPdmQaq6RqwA/ofX5XRmRL2tQPCDh5ANV0D7TFf3j+J9oQwRw1YXg1kCTdWUGVWEIP1FRPTNdD0iZZ/ubS8GkjxA7QequkasLyqQAfyGjh6izu/UxU4q30FsQIbXfYS6v0CADWQnWkdtB0Qpms8Lqg9b9RAe6JAj/8YLtXyiab/zzAAWN5N+BtKvBaQ17DOKgAAAABJRU5ErkJggg=="
    ,"phone" => "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAABGdBTUEAAK/INwWK6QAAABl0RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAF6SURBVDjLjZO/S8NAFMe/l8Q0ASUUXRwK9R9wFDfdunV19Q9wcmg3/wHp4FLo4CA4Ce3o6OLWUZwKpbRLMdDFCKH5dd73SkvQkvTgeLnLe5/3vXfvhJQSu4xutyuDIEC73Rb5fQM7jizLMBwO/+1b+UWv1+soRZdCiGO1PFJzT33r4Hq9DsuyigFRFN02Gg1UKpWNc5qmehJimmYxgE6e5+GsX4VrZQgzHlfiwI7xdP5VroAOzCZMidaFgGVIENH5sPAdZeUAwzAQxzGECrSpVt0Qq0ygErKbAh5DqOC7dxWj0gtKEGSl5QAWiYCX009t18Wj9UxvK8DYBugHz3hN+hiNRnp9+PAINlzpLawBTedqlflkpcC/uUYVKFewrsF4PNZ2MpnozLPZbJOg9AgMYNdx0BJUq9U2CQoBvEYGzOdz2LYN3/fhOA4Wi4UG839hDVTf/4RhuJ9XwLdAy/5Qr1EWAqbT6f1gMGgul0sdmAMjSRK4rvv2F/ALQmi5wbpDa1QAAAAASUVORK5CYII="
    ,"tickets" => "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAABb0lEQVQ4jZWToYrDQBCG771WLKwKZEUKiVuzYs2KrGjYwJIXaEsXStsXKkRErKiJqKmJqKgIE6oi5syFXu+4azvwwfwwP/wMMx8fL1RVVb6qKqiqyr8y/1DOOe+cg9vths45eMtclqW31sIwDDgMA1prwVoLZVk+TzKfz31RFND3Pe73+7Hve5woiuL/JHmee2MMXK9XnNjtduPUG2PAGAN5nv9OorX2Wmu4XC74k+12O37XWuvHJEopr5SCruvwLzabzdh1HSqlQCl1TyCl9FJKOJ/P+AwpJUgp72YhhBdCwOl0wmcIIUAIcTenaeqzLIO2bXG9Xo9t2+JfZFkGaZo+Li5JEjgejzixWq3G73oiSRKYzWa/tx7HseecA+ccQggYQsDlcjlOfQgBOecQx/H/xxNFETRNgxOLxWJsmgajKIIoip5fHmPMM8aAMQZ1XWNd1/il33sgSikcDgeklAKl9P3vI4R4QggQQl4yfwL33Y40unwhHQAAAABJRU5ErkJggg=="
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
    $role = $_POST["role"];
	// If we are adding someone to the schedule . . .
	if ($action == "Add") {
		// Make sure they entered something.
		if ($name == "" || $name == null) {
			echo "<p class='center'>Enter a name, fool!</p>\n";
		} else {
			// Add to the database.
			$name = sanitize($name);
			add_to_schedule($name, $time, $role);
		}
	} elseif ($action == "Remove") {
		// Clear from the database for the current day.
		$id = $_POST["clear"];
		del_from_schedule($id);
		}
}

show_schedule($times, $roles);

echo "<p class='center'>Entries expire after 9 hours (from the time you submit them, not the time of the lunch break.)</p>\n";

// Vendor Schedule
require_once('vendor.inc');

// Close out the HTML.
html_footer();

?>
