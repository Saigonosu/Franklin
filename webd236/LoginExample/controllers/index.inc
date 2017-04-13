<?php
include_once "include/util.inc";
include_once "models/todo.inc";
include_once "controllers/todo.inc";

function get_index($params) {
    get_list($params);
}

?>