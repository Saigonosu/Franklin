<?php
include_once 'models/db.inc';
include_once 'models/question.inc';

function findUserById($id) {
    global $db;
    $st = $db -> prepare("
        SELECT
            *
        FROM
            users
        WHERE
            id = :id
    ");
    $st -> bindParam(':id', $id);
    $st -> execute();
    return $st -> fetch(PDO::FETCH_ASSOC);
}

function addUser($user) {
    if (hasId($user)) {
        die('Attempt to add user that already has an id');
    }
    global $db;
    $statement = $db -> prepare("
        INSERT INTO users
           (firstName, lastName, email, password)
        VALUES
           (:firstName, :lastName, :email, :password)
    ");
    $statement -> bindParam(':firstName', $user['firstName']);
    $statement -> bindParam(':lastName', $user['lastName']);
    $statement -> bindParam(':email', $user['email']);
    $statement -> bindParam(':password', $user['password']);
    $statement -> execute();
    return $db -> lastInsertId();
}

function hasId($user) {
    return isset($user['id']) && !empty($user['id']);
}

function updateUser($user) {
    if (!hasId($user)) {
        die('attempt to update user without id');
    }
    global $db;
    $statement = $db -> prepare("
        UPDATE
            users
        SET
            firstName=:firstName,
            lastName=:lastName,
            email=:email,
            password=:password
        WHERE
            id=:id");
    $statement -> bindParam(':firstName', $user['firstName']);
    $statement -> bindParam(':lastName', $user['lastName']);
    $statement -> bindParam(':email', $user['email']);
    $statement -> bindParam(':password', $user['password']);
    $statement -> bindParam(':id', $user['id']);
    return $statement -> execute();
}

function deleteUser($id) {
    global $db;
    // must first delete all questions by that user first
    deleteQuestionsByUserId($id);

    $statement = $db -> prepare("
        DELETE FROM
            users
        WHERE
            id = :id
    ");
    $statement -> bindParam(':id', $id);
    $statement -> execute();
}

function findUserByEmail($email) {
    global $db;
    $st = $db -> prepare("
        SELECT
            *
        FROM
            users
        WHERE
            email = :email
    ");
    $st -> bindParam(':email', $email);
    $st -> execute();
    return $st -> fetch(PDO::FETCH_ASSOC);
}

function findByEmailAndPassword($email, $password) {
    $user = findUserByEmail($email);
    if ($user && $user['password'] === $password) {
        return $user;
    }
    return false;
}

function addOrUpdateUser($user) {
    global $db;
    if (isset($user['id']) && $user['id'] != '') {
        updateUser($user);
    } else {
        $user['id'] = addUser($user);
        $_SESSION['userid'] = $user['id'];
        $_SESSION['name'] = "${user['firstName']} ${user['lastName']}";

    }
}
?>
