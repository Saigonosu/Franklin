<?php
include_once 'models/db.inc';

function findRecentQuestions($count = 5) {
    global $db;
    $st = $db -> prepare('SELECT * FROM questions ORDER BY postedOn DESC LIMIT :limit');
    $st -> bindParam(':limit', $count);
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}

function findQuestionById($id) {
    global $db;
    $st = $db -> prepare('SELECT * FROM questions WHERE id = :id');
    $st -> bindParam(':id', $id);
    $st -> execute();
    return $st -> fetch(PDO::FETCH_ASSOC);
}

function findQuestionsByUserId($userId, $limit=false) {
    global $db;
    $query = 'SELECT * FROM questions WHERE userId=:userId ORDER BY postedOn DESC';
    if ($limit) {
        $query .= ' LIMIT :limit';
    }
    $st = $db -> prepare($query);
    $st -> bindParam(':userId', $userId);
    if ($limit) {
        $st -> bindParam(':limit', $limit);
    }
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}


function addQuestion($question) {
    global $db;
    $statement = $db -> prepare("INSERT INTO questions (postedOn, title, content, tags, userId) VALUES (DATE('now'), :title, :content, :tags, :userId)");
    $statement -> bindParam(':title', $question['title']);
    $statement -> bindParam(':content', $question['content']);
    $statement -> bindParam(':tags', $question['tags']);
    $statement -> bindParam(':userId', $_SESSION['userid']);
    $statement -> execute();
    return $db -> lastInsertId();
}

function updateQuestion($question) {
    global $db;
    $statement = $db -> prepare("UPDATE questions SET title=:title, content=:content, tags=:tags WHERE id=:id");
    $statement -> bindParam(':title', $question['title']);
    $statement -> bindParam(':content', $question['content']);
    $statement -> bindParam(':tags', $question['tags']);
    $statement -> bindParam(':id', $question['id']);
    return $statement -> execute();
}

function deleteQuestion($id) {
    global $db;
    $statement = $db -> prepare("DELETE FROM questions WHERE id = :id");
    $statement -> bindParam(':id', $id);
    $statement -> execute();
}

function deleteQuestionsByUserId($userId) {
    global $db;
    $statement = $db -> prepare("DELETE FROM questions WHERE userId = :userId");
    $statement -> bindParam(':userId', $userId);
    $statement -> execute();
}

function addOrUpdateQuestion($question) {
    global $db;
    if (isset($question['id']) && $question['id'] != '') {
        updateQuestion($question);
    } else {
        addQuestion($question);
    }
}
?>
