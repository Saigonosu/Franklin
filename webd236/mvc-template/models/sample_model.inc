<?php
include_once 'models/db.inc';

// This is the sample RECORDS MODEL...

// Assumes table named 'table1' with fields:
//    id (integer, primary key)
//    field1 (whatever type)
//    field2 (whatever type)
//    field3 (whatever type)
//    ...

// FINDER FUNCTIONS...

// Function to return all records in table1.  Takes no parameters...
function model_findAllRecords() {
    global $db;

    $sql = 'SELECT * FROM table1 ORDER BY id ASC';
    $statement = $db -> prepare($sql);
    $statement -> execute();
    return $statement -> fetchAll(PDO::FETCH_ASSOC);
}


// Function to return a single record from table1 by record_id....
function model_findRecordByID($id) {
      global $db;

    $sql = "SELECT * FROM table1 WHERE id = :id";
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
    return $statement -> fetch(PDO::FETCH_ASSOC);
}


// Sample Add Function...
function model_addRecord($field1, $field2, $field3 /* ... */) {
    global $db;

    $sql = 'INSERT INTO table1 (field1, field2, field3) VALUES (:field1, :field2, :field3)';
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':field1', $field1);
    $statement -> bindParam(':field2', $field2);
    $statement -> bindParam(':field3', $field3);
    $statement -> execute();
    return $db -> lastInsertId();
}


// Sample Update Function...
function model_updateRecord($id, $field1, $field2, $field3 /*...*/ ) {
    global $db;

    $sql = 'UPDATE table1 SET field1 = :field1, field2 = :field2, field3 = :field3 WHERE id = :id';
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':field1', $field1);
    $statement -> bindParam(':field2', $field2);
    $statement -> bindParam(':field3', $field3);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
}


// Sample Delete Function...
function model_deleteRecord($id) {
    global $db;

    $sql = "DELETE FROM table1 WHERE id = :id";
    $statement = $db -> prepare($sql);
    $statement -> bindParam(':id', $id);
    $statement -> execute();
}
?>
