<?php
include_once "include/util.inc";
include_once "models/User.inc";

function get_index($params) {
    // @formatter:off
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
        )
    );
    // @formatter:on
}

function post_index($params) {
    $email = safeParam($_REQUEST, 'email', false);
    $password = safeParam($_REQUEST, 'password', false);
    $user = User::findByEmailAndPassword($email, $password);
    if ($user) {
        $_SESSION['userid'] = $user -> getId();
        if (isset($_SESSION['redirect'])) {
            redirect($_SESSION['redirect']);
            exit();
        }
        redirectRelative("index");
    } else {
        // @formatter:off
        renderTemplate(
            "views/login_form.inc",
            array(
                'title' => 'Login',
                'errors' => array("Invalid username/password"),
                'email' => $email,
                'password' => $password
            )
        );
        // @formatter:on
    }
}
?>