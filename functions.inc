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

?>
