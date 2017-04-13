<?php
include_once 'include/util.inc';

// This is the "home page", which redirects to the index controller
// (controllers/index.inc) get_index() function, which may redirect to
// the actual home page controller/function...
redirect("index");

// Alternatively, you could just include your home page controller directly,
// include_once 'controllers/sample.inc';
// and then call the home-page function (get_index, in this case)
// get_index();
?>
