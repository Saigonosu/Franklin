<?php
include_once "include/util.inc";
include_once "controllers/sample.inc";

function get_index($params) {
	// This Handles the /, /index, and /index/index urls.
	
    // redirect to the sample controller get_list() function...
    get_list($params);
}

?>
