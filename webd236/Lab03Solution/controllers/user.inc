<?php
include_once "include/util.inc";
include_once "models/user.inc";
include_once "models/question.inc";
include_once "controllers/logout.inc";

function safeParam($arr, $index, $default) {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}

function validatePresent($array, $key, $message, &$errors) {
    if (!isset($array[$key]) || trim($array[$key]) == '') {
        $errors[] = $message;
        return false;
    }
    return true;
}

function clean($array) {
    foreach ($array as $key => $value) {
        $array[$key] = htmlentities(trim($value));
    }
    return $array;
}

function validateUser($user) {
    $errors = array();
    validatePresent($user, 'firstName', 'First name is required', $errors);
    validatePresent($user, 'lastName', 'Last name is required', $errors);
    validatePresent($user, 'email', 'E-mail address is required', $errors);
    validatePresent($user, 'password', 'Password is required', $errors);
    return $errors;
}

function get_register($params) {
    renderTemplate(
        "views/user_form.inc",
        array(
            'title' => 'Register',
            'user' => array()
        )
    );
}

function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No user id specified");
    }

    $user = findUserById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    $questions = findQuestionsByUserId($id);
    renderTemplate(
        "views/user_view.inc",
        array(
            'title' => 'View user',
            'user' => $user,
            'questions' => $questions
        )
    );
}

function get_edit($params) {
    $id = safeParam($params, 0, false);

    ensureLoggedInUserIs($id);

    if ($id === false) {
        die("No user id specified");
    }

    $user = findUserById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    renderTemplate(
        "views/user_form.inc",
        array(
            'title' => 'Edit user',
            'user' => $user
        )
    );
}

function post_edit($params) {
    $user = safeParam($_REQUEST, 'user', false);
    $errors = validateUser($user);
    clean($user);

    $other = findUserByEmail($user['email']);
    if ($other && $other['id'] != $user['id']) {
        $errors[] = "email address is already in use.";
    }

    if (count($errors)) {
        renderTemplate(
            "views/user_form.inc",
            array(
                'title' => 'Edit user',
                'errors' => $errors,
                'user' => $user
            )
        );
        return;
    }
    clean($user);
    addOrUpdateUser($user);
    redirectRelative("index");
}

function get_delete($params) {
    $id = safeParam($params, 0, false);

    ensureLoggedInUserIs($id);

    if ($id === false) {
        die("No user id specified");
    }

    $user = findUserById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    deleteUser($id);
    logout();
}

?>
