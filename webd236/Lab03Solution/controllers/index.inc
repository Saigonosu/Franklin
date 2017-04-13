<?php
include_once "include/util.inc";
include_once "models/question.inc";
include_once "controllers/question.inc";

function get_index($params) {
    $questions = findRecentQuestions(5);
    renderTemplate(
        "views/index.inc",
        array(
            'title' => "My Question and Answer Forum",
            'questions' => $questions
        )
    );
}
?>
