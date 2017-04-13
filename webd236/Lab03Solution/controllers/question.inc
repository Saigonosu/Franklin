<?php
include_once "include/util.inc";
include_once "models/question.inc";

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

function get_add($params) {
    renderTemplate(
        "views/question_edit_form.inc",
        array(
            'title' => 'Add a question',
            'question' => array(
                'title' => '',
                'content' => '',
                'id' => '',
            )
        )
    );
}

function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No question id specified");
    }

    $question = findQuestionById($id);
    if (!$question) {
        die("No question with id $id found.");
    }
    renderTemplate(
        "views/question_view_long.inc",
        array(
            'title' => $question['title'],
            'question' => $question
        )
    );
}

function get_edit($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No question id specified");
    }

    $question = findQuestionById($id);
    if (!$question) {
        die("No question with id $id found.");
    }

    ensureLoggedInUserIs($question['userId']);

    renderTemplate(
        "views/question_edit_form.inc",
        array(
            'title' => 'Edit a question',
            'question' => $question
        )
    );
}

function validateQuestion($question) {
    $errors = array();
    validatePresent($question, 'title', 'Title is required', $errors);
    validatePresent($question, 'content', 'Content is required', $errors);
    return $errors;
}

function post_edit($params) {
    $question = safeParam($_REQUEST, 'question', false);
    $errors = validateQuestion($question);

    if (count($errors)) {
        renderTemplate(
            "views/question_edit_form.inc",
            array(
                'title' => 'Edit a question',
                'errors' => $errors,
                'question' => $question
            )
        );
        return;
    }
    clean($question);
    addOrUpdateQuestion($question);
    redirectRelative("index");
}

function get_delete($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No question id specified");
    }

    $question = findQuestionById($id);
    if (!$question) {
        die("No question with id $id found.");
    }

    ensureLoggedInUserIs($question['userId']);

    deleteQuestion($id);
    redirectRelative('index');
}

?>
