<?php
include_once 'models/Model.inc';

class Todo extends Model {
    private $description;
    private $done;

    //public function __construct($id, $description, $done = false) {
    public function __construct($fields = array()) {
        parent::__construct($fields);
        $this -> setDescription(safeParam($fields, 'description'));
        $this -> setDone(safeParam($fields, 'done'));
    }

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('description', $this -> description, "Description is required");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private function clean() {
        $this -> description = htmlentities($this -> description, ENT_QUOTES);
    }

    public function getDescription() {
        return $this -> description;
    }

    public function setDescription($description) {
        $this -> description = $description;
        return $this;
    }

    public function getDone() {
        return $this -> done;
    }

    public function setDone($done) {
        $this -> done = $done;
        return $this;
    }

    static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM todo WHERE id = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new Todo($row);
    }

    private static function fromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = new Todo($row);
        }
        return $result;
    }

    static function findAllCurrent() {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM todo WHERE done = 0 ORDER BY id');
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    static function findAllDone() {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM todo WHERE done != 0 ORDER BY id');
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    function insert() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO todo (description, done) values (:description, 0)");
        $statement -> bindParam(':description', $this -> description);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
        $this -> validate(true);
        $this -> clean();
        $db = Db::getDb();
        $statement = $db -> prepare("UPDATE todo SET description = :description, done = :done WHERE id = :id");
        $statement -> bindParam(':description', $this -> description);
        $statement -> bindParam(':done', $this -> done);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    function delete() {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM todo WHERE id = :id");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
    }

}
?>
