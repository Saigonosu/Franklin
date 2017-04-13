<?php
include_once 'models/Model.inc';
include_once 'models/Group.inc';
include_once 'models/Validator.inc';

class User extends Model {

    protected $firstName;
    protected $lastName;
    protected $email;
    protected $password;

    function __construct($fields = array()) {
        parent::__construct($fields);
        $this -> mergeFields($fields);
    }

    public function mergeFields($fields) {
        $names = array('firstName', 'lastName', 'email', 'password');
        foreach ($names as $field) {
            if (isset($fields[$field])) {
                $this -> $field = $fields[$field];
            }
        }
    }

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('firstName', $this -> firstName, "First name is required");
        $validator -> required('lastName', $this -> lastName, "Last name is required");
        $validator -> email('email', $this -> email, "Invalid email address");
        $validator -> password('password', $this -> password, "Password must be at least 8 chars, have an upper case character, a symbol, and a number");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private function clean() {
        $this -> firstName = htmlentities($this -> firstName, ENT_QUOTES);
        $this -> lastName = htmlentities($this -> lastName, ENT_QUOTES);
        $this -> email = htmlentities($this -> email);
    }

    public function getFullName() {
        return "{$this-> firstName} {$this->lastName}";
    }

    public function setFirstName($firstName) {
        $this -> firstName = trim($firstName);
    }

    public function getFirstName() {
        return $this -> firstName;
    }

    public function setLastName($lastName) {
        $this -> lastName = trim($lastName);
    }

    public function getlastName() {
        return $this -> lastName;
    }

    public function setEmail($email) {
        $this -> email = trim($email);
    }

    public function getEmail() {
        return $this -> email;
    }

    public function setPassword($password) {
        $this -> password = trim($password);
    }

    public function getPassword() {
        return $this -> password;
    }

    public function getGroups() {
        return Group::findByUserId($this -> id);
    }

    public static function fromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = new User($row);
        }
        return $result;
    }

    public static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM users WHERE id = :id");
        $st -> bindParam(':id', $id);
        $st -> execute();
        return new User($st -> fetch(PDO::FETCH_ASSOC));
    }

    public function insert() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("INSERT INTO users (firstName, lastName, email, password) VALUES (:firstName, :lastName, :email, :password)");
        $statement -> bindParam(':firstName', $this -> firstName);
        $statement -> bindParam(':lastName', $this -> lastName);
        $statement -> bindParam(':email', $this -> email);
        $statement -> bindParam(':password', $this -> password);
        $statement -> execute();
        $this -> setId($db -> lastInsertId());

        $group = Group::findByName('Users');
        $group -> addUser($this);

        return $this;
    }

    public function update() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("UPDATE users SET firstName=:firstName, lastName=:lastName, email=:email, password=:password WHERE id=:id");
        $statement -> bindParam(':firstName', $this -> firstName);
        $statement -> bindParam(':lastName', $this -> lastName);
        $statement -> bindParam(':email', $this -> email);
        $statement -> bindParam(':password', $this -> password);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    public function delete() {
        self::deleteById($this -> getId());
    }

    private static function deleteById($id) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM users WHERE id = :id");
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }

    public static function findAll() {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM users");
        $st -> execute();
        return self::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findByEmail($email) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM users WHERE email = :email");
        $st -> bindParam(':email', $email);
        $st -> execute();
        return new User($st -> fetch(PDO::FETCH_ASSOC));
    }

    public static function findByEmailAndPassword($email, $password) {
        $user = self::findByEmail($email);
        if ($user -> getPassword() === $password) {
            return $user;
        }
        return false;
    }

    public function insertOrUpdate() {
        $login = !$this -> id;
        $user = parent::insertOrUpdate();
        if ($login) {
            $_SESSION['userid'] = $user -> getId();
        }
    }

}
?>