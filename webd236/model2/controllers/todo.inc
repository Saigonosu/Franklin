<?php
include_once "include/util.inc";
include_once "models/todo.inc";

function safeParam($arr, $index, $default) {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}

function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No todo id specified");
    }
    
    $todo = findToDoById($id);
    if (!$todo) {
        die("No todo with id $id found.");
    }
    // @formatter:off
    renderTemplate(
        "views/todo_view.inc",
        array(
            'title' => 'Viewing To Do',
            'todo' => $todo
        )
    );
    // @formatter:on
}

function get_list($params) {
    $todos = findAllCurrentToDos();
    $dones = findAllDoneToDos();
    // @formatter:off
    renderTemplate(
        "views/index.inc",
        array(
            'title' => 'To Do List',
            'todos' => $todos,
            'dones' => $dones
        )
        
    );
    // @formatter:on
}

function get_edit($params) {
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No todo specified");
    }
    $todo = findToDoById($id);
    if (!$todo) {
        die("No todo found.");
    }
    // @formatter:off
    renderTemplate(
        "views/todo_edit.inc",
        array(
            'title' => 'Editing To Do',
            'todo' => $todo
        )
    );
    // @formatter:on
}

function post_add($params) {
    if (!isset($_POST['description'])) {
        die("no description given");
    }
    $description = htmlentities($_POST['description']);
    addToDo($description);
    redirectRelative("index");
}

function validate_present($elements) {
    $errors = '';
    foreach ($elements as $element) {
        if (!isset($_POST[$element])) {
            $errors .= "Missing $element\n";
        }
    }
    return $errors;
}

function post_update($params) {
    $errors = validate_present(array('id', 'description', 'done'));
    if ($errors) {
        die($errors);
    }
    $id = $_POST['id'];
    $description = $_POST['description'];
    $done = $_POST['done'];
    updateToDo($id, $description, $done);
    redirectRelative("todo/view/$id");
}

function get_delete($params) {
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No todo specified");
    }
    $todo = findToDoById($id);
    if (!$todo) {
        die("No todo found.");
    }
    deleteToDo($id);
    redirectRelative("index");
}
?>