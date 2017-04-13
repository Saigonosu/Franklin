<?php
include_once "include/util.inc";
include_once "models/user.inc";

function safeParam($arr, $index, $default) {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}

function get_index($params) {
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
        )
    );
}

function post_index($params) {
    $email = safeParam($_REQUEST, 'email', false);
    $password = safeParam($_REQUEST, 'password', false);
    $user = findByEmailAndPassword($email, $password);
    if ($user) {
        $_SESSION['userid'] = $user['id'];
        $_SESSION['name'] = "${user['firstName']} ${user['lastName']}";
        if (isset($_SESSION['redirect'])) {
            $redirect = $_SESSION['redirect'];
            redirect($redirect);
            exit();
        }
        redirectRelative("index");
    } else {
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
            'errors' => array("Invalid username/password"),
            'email' => $email,
            'password' => $password
        )
    );
    }
}
?>
