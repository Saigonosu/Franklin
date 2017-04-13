<?php
include_once "include/util.inc";
include_once "models/sample_model.inc";

// This is the sample RECORDS CONTROLLER...

// Handles the home page...
// Display a list of records...
function get_list($params) {
	// handles the /sample/list url
	
    $records = model_findAllRecords();

    renderTemplate(
        "views/record_list.inc",
        array(
            'title' => 'Records List',
            'records' => $records
        )
    );
}


// Handles viewing one individual record...
function get_view($params) {
	// handles the /sample/view/# url, where # is passed as $params[0]
	
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No Record selected");
    }

    $record = model_findRecordByID($id);
    if (!$record) {
        die("No record with id $id found.");
    }

    renderTemplate(
        "views/record_view.inc",
        array(
            'title' => 'Viewing Record Info',
            'record' => $record
        )
    );
}


// Handles loading record edit form view...
function get_edit($params) {
	// handles the /sample/edit/# url, where # is passed as $params[0]
	
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }

    $record = model_findRecordByID($id);
    if (!$record) {
        die("No record found.");
    }

    renderTemplate(
        "views/record_edit.inc",
        array(
            'title' => 'Editing Record',
            'record' => $record
        )
    );
}


// function to validate whether elements have been provided in $_POST....
function validate_present($elements) {
    $errors = '';
    foreach ($elements as $element) {
        if (!isset($_POST[$element]) || empty($_POST[$element])) {
            $errors .= "Missing $element<br />\n";
        }
    }
    return $errors;
}


// Handles adding a new record with 3 fields...
function post_add($params) {
	// handles the /sample/add url submitted from the add form.  The form values
	// are passed in the $_POST array.
	
    // Validate that all required parameters are set
    // and theoretically that they are all of correct type....
    $errors = validate_present(array('field1', 'field2', 'field3'));
    if ($errors) {
        die($errors);
    }
    $field1 = htmlentities($_POST['field1']);
    $field2 = htmlentities($_POST['field2']);
    $field3 = htmlentities($_POST['field3']);

    $id = model_addRecord($field1, $field2, $field3);
    // show them the record they just created...
    redirectRelative("sample/view/$id");
}


// Handle Updating an existing record identified by id...
function post_edit($params) {
	// handles the /sample/edit url submitted from the edit form.  The form values are
	// passed in the $_POST array.
	
    $errors = validate_present(array('id', 'field1', 'field2', 'field3'));
    if ($errors) {
        die($errors);
    }
    $id = $_POST['id'];
    $field1 = htmlentities($_POST['field1']);
    $field2 = htmlentities($_POST['field2']);
    $field3 = htmlentities($_POST['field3']);

    model_updateRecord($id, $field1, $field2, $field3);
    redirectRelative("sample/view/$id");
}


// Handle a request to delete a record by id...
function get_delete($params) {
	// handles the /sample/delete/# url, where # is passed in $params[0]
	
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }

    $record = model_findRecordByID($id);
    if (!$record) {
        die("No record found.");
    }

    model_deleteRecord($id);
    // send focus back to the home page...
    redirectRelative("index");
}

?>
