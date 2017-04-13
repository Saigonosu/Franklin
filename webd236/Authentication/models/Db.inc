<?php
include_once ('models/Permission.inc');
include_once ('models/User.inc');
include_once ('models/Group.inc');
include_once ('include/Logger.inc');

class Db {
    public static function getDb() {
        try {
            $fileName = "ToDoList.db3";

            // see if we need to create tables
            $makeDb = !file_exists($fileName);
            $db = new PDO("sqlite:${fileName}");

            // force exceptions for better debugging.
            $db -> setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

            // force cascading deletes on foreign key constraints
            $st = $db -> prepare("PRAGMA foreign_keys = ON");
            $st -> execute();

            if ($makeDb) {
                self::makeTables($db);
                self::populateTables($db);
            }

        } catch (PDOException $e) {
            die("Could not open database. " . $e -> getMessage());
        }
        return $db;
    }

    private static function makeTables(&$db) {
        
        Logger::instance() -> info("Creating tables");
        // @formatter:off
        $statements = array( 
            "CREATE TABLE users (
                id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                email TEXT NOT NULL,
                password TEXT NOT NULL,
                firstName TEXT NOT NULL,
                lastName TEXT NOT NULL
            )",
            "CREATE TABLE groups (
                id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            )",
            "CREATE TABLE permissions (
                id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            )",
            "CREATE TABLE usergroups (
                userId INTEGER NOT NULL,
                groupId INTEGER NOT NULL,
                FOREIGN KEY(userId) REFERENCES users(id) ON DELETE CASCADE,
                FOREIGN KEY(groupId) REFERENCES groups(id) ON DELETE CASCADE
            )",
            "CREATE TABLE grouppermissions (
                permissionId INTEGER NOT NULL,
                groupId INTEGER NOT NULL,
                FOREIGN KEY(permissionId) REFERENCES permissions(id) ON DELETE CASCADE,
                FOREIGN KEY(groupId) REFERENCES groups(id) ON DELETE CASCADE
            )",
            "CREATE TABLE todo (
                id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                description VARCHAR(50) NOT NULL,
                done INTEGER NOT NULL
            )"
        );
        // @formatter:on

        $db -> beginTransaction();
        foreach ($statements as $statement) {
            $st = $db -> prepare($statement);
            $st -> execute();
        }
        $db -> commit();
    }

    private static function populateTables(&$db) {
        // create the permissions
        $userperms = array('create_todo', 'edit_todo', 'delete_todo', 'view_todo');
        $adminperms = array('admin_page', 'edit_user', 'delete_user', 'view_user');
        $permissions = array();
        $allperms = array($adminperms, $userperms);
        foreach ($allperms as $perms) {
            foreach ($perms as $name) {
                $p = new Permission( array('name' => $name));
                $p -> insert();
                $permissions[$name] = $p;
            }
        }

        // set up Users group for new registrants
        Logger::instance() -> info("Creating default Users group.");
        $g = new Group( array('name' => 'Users'));
        $g -> insert();
        foreach ($userperms as $name) {
            $g -> addPermission($permissions[$name]);
        }

        // set up the super-user
        Logger::instance() -> info("Creating default Administrators group.");
        $u = new User( array('firstName' => 'System', 'lastName' => 'Administrator', 'email' => 'admin@example.com', 'password' => 'asdF123$'));
        $u -> insert();
        $g = new Group( array('name' => 'Administrators'));
        $g -> insert();
        $g -> addUser($u);
        foreach ($adminperms as $name) {
            $g -> addPermission($permissions[$name]);
        }

    }
}
?>
