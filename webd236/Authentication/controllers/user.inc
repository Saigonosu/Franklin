<?php
include_once "include/util.inc";
include_once "include/Authenticator.inc";
include_once "models/User.inc";
include_once "models/Group.inc";

function ensureLoggedInUserIs($id) {
    $userId = safeParam($_SESSION, 'userid');
    if ($id !== $userId) {
        throw new Exception("Can't edit");
    }
}

function get_register($params) {
    // @formatter:off
    renderTemplate(
        "views/user_form.inc",
        array(
            'title' => 'Register',
            'user' => new User(),
            'action' => 'user/register'
        )
    );
    // @formatter:on
}

function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No user id specified");
    }

    if (!Authenticator::instance() -> can('view_user')) {
        ensureLoggedInUserIs($id);
    }
    
    $user = User::findById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    // @formatter:off
    renderTemplate(
        "views/user_view.inc",
        array(
            'title' => 'View user',
            'user' => $user
        )
    );
    // @formatter:on
}

function get_edit($params) {
    $id = safeParam($params, 0, false);

    if (!Authenticator::instance() -> can('edit_user')) {
        ensureLoggedInUserIs($id);
    }

    if ($id === false) {
        die("No user id specified");
    }

    $user = User::findById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    // @formatter:off
    renderTemplate(
        "views/user_form.inc",
        array(
            'title' => 'Edit user',
            'user' => $user,
            'action' => 'user/edit'
        )
    );
    // @formatter:on
}

function post_edit($params) {
    $user = safeParam($_REQUEST, 'user', false);
    $user = new User($user);

    if (!Authenticator::instance() -> can('edit_user')) {
        ensureLoggedInUserIs($user->getId());
    }
    
    $validator = $user -> validate();

    $other = User::findByEmail($user -> getEmail());
    if ($other && $other -> getId() != $user -> getId()) {
        $validator -> addError('email', "Email address is aready in use.");
    }

    if ($validator -> hasErrors()) {
        // @formatter:off
        renderTemplate(
            "views/user_form.inc",
            array(
                'title' => 'Edit user',
                'errors' => $validator->allErrors(), 
                'user' => $user,
                'action' => 'user/edit'
            )
        );
        // @formatter:on
        return;
    }
    $user -> insertOrUpdate();
    redirectRelative("index");
}

function post_register($params) {
    $user = safeParam($_REQUEST, 'user', false);
    $user = new User($user);

    $validator = $user -> validate();

    $other = User::findByEmail($user -> getEmail());
    if ($other && $other -> getId() != $user -> getId()) {
        $validator -> addError('email', "Email address is aready in use.");
    }

    if ($validator -> hasErrors()) {
        // @formatter:off
        renderTemplate(
            "views/user_form.inc",
            array(
                'title' => 'Edit user',
                'errors' => $validator->allErrors(), 
                'user' => $user,
                'action' => 'user/register'
            )
        );
        // @formatter:on
        return;
    }
    $user -> insertOrUpdate();
    redirectRelative("index");
}

function get_delete($params) {
    $id = safeParam($params, 0, false);

    if (!Authenticator::instance() -> can('delete_user')) {
        ensureLoggedInUserIs($id);
    }

    if ($id === false) {
        die("No user id specified");
    }

    $user = User::findById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    $user -> delete();
    logout();
}

function get_manage($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $users = User::findAll();
    // @formatter:off
    renderTemplate(
        "views/user_list.inc",
        array(
            "title" => "Manage users",
            "users" => $users
        )
    );
    // @formatter:on
}

function get_groups($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No user id specified");
    }
    $user = User::findById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    $memberOf = Group::findByUserId($id);
    $notMemberOf = Group::findByNotUserId($id);
    renderTemplate(
        "views/user_groups.inc",
        array(
            "title" => "{$user->getFullName()}'s Groups",
            "memberOf" => $memberOf,
            "notMemberOf" => $notMemberOf,
            "user" => $user
        )
    );
}
?>