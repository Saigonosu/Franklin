<?php
include_once 'models/db.inc';

function findToDoById($id) {
    global $db;
    $st = $db -> prepare('SELECT * FROM todo WHERE id = ?');
    $st -> bindParam(1, $id);
    $st -> execute();
    return $st -> fetch(PDO::FETCH_ASSOC);
}

function findAllCurrentToDos() {
    global $db;
    $st = $db -> prepare('SELECT * FROM todo WHERE done = 0 ORDER BY id');
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}

function findAllDoneToDos() {
    global $db;
    $st = $db -> prepare('SELECT * FROM todo WHERE done != 0 ORDER BY id');
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}

function addToDo($description) {
    global $db;
    $statement = $db -> prepare("INSERT INTO todo (description, done) values (?, 0)");
    $statement -> bindParam(1, $description);
    $statement -> execute();
    return $db->lastInsertId();
}

function updateToDo($id, $description, $done) {
    global $db;
    $statement = $db -> prepare("UPDATE todo SET description = ?, done = ? WHERE id = ?");
    $statement -> bindParam(1, $description);
    $statement -> bindParam(2, $done);
    $statement -> bindParam(3, $id);
    $statement -> execute();
}

function deleteToDo($id) {
    global $db;
    $statement = $db -> prepare("DELETE FROM todo WHERE id = ?");
    $statement -> bindParam(1, $id);
    $statement -> execute();
}
?>