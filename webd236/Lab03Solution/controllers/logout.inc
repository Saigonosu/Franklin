<?php
include_once "include/util.inc";

function logout() {
    $_SESSION = array();
    session_destroy();
    redirectRelative("index");
}

function get_index($params) {
    logout();
}
?>
