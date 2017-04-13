<?php
include_once "include/util.inc";
include_once "include/Authenticator.inc";
include_once "models/Todo.inc";
include_once "models/validator.inc";

function get_view($params) {
    Authenticator::instance() -> ensure('view_todo');

    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No todo id specified");
    }

    $todo = Todo::findById($id);
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
    $todos = Todo::findAllCurrent();
    $dones = Todo::findAllDone();
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
    Authenticator::instance() -> ensure('edit_todo');

    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No todo specified");
    }
    $todo = Todo::findById($id);
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
    Authenticator::instance() -> ensure('create_todo');

    $todo = safeParam($_REQUEST, 'todo', false);
    $todo = new Todo($todo);
    $validator = $todo -> validate();

    if (!$validator -> hasErrors()) {
        $todo -> insert();
    }
    redirectRelative("index");
}

function post_update($params) {
    Authenticator::instance() -> ensure('edit_todo');

    $id = trim(safeParam($_POST, 'id'));
    $description = trim(safeParam($_POST, 'description'));
    $done = trim(safeParam($_POST, 'done'));

    $validator = new Validator();
    $validator -> required('id', $id, 'No ID specified');
    $validator -> required('description', $description, 'Description required');
    $validator -> required('done', $done, "Done is required");

    if (!$validator -> hasErrors()) {
        $todo = Todo::findById($id);
        if ($todo) {
            $todo -> setDescription($description);
            $todo -> setDone($done);
            $todo -> update();
        }
        redirectRelative("todo/view/$id");
    }

    // @formatter:off
    $todo = new Todo($id, $description, $done);
    renderTemplate(
        "views/todo_edit.inc",
        array(
            'title' => 'Editing To Do',
            'errors' => $validator -> allErrors(),
            'todo' => $todo
        )
    );
    // @formatter:on
}

function get_delete($params) {
    Authenticator::instance() -> ensure('delete_todo');

    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No todo specified");
    }
    $todo = Todo::findById($id);
    if (!$todo) {
        die("No todo found.");
    }
    $todo -> delete();
    redirectRelative("index");
}
?>