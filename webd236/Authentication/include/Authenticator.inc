<?php
include_once "models/Db.inc";
include_once "models/Permission.inc";
include_once "include/util.inc";

class Authenticator {

    private $cache;
    private static $instance;

    // @formatter:off
    const PERMS_QUERY =
        "SELECT DISTINCT permissions.id as id, permissions.name as name
         FROM
            users, usergroups, groups, grouppermissions, permissions
         WHERE
            users.id = :userId AND
            users.id = usergroups.userId AND
            usergroups.groupId = groups.id AND
            groups.id = grouppermissions.groupId AND
            grouppermissions.permissionId = permissions.id";
    // @formatter:on

    private function __construct() {
        $cache = array();
    }

    public static function instance() {
        if (!isset(self::$instance)) {
            self::$instance = new Authenticator();
        }
        return self::$instance;
    }

    private function realUserId($userId) {
        if (isset($userId) && is_numeric($userId)) {
            return $userId;
        }
        if (gettype($userId) == 'object') {
            return $userId -> getId();
        }
        return currentUser();
    }

    public function can($permissionKey, $userId = false) {
        $userId = $this -> realUserId($userId);
        $permissions = $this -> permissionsFor($userId);
        foreach ($permissions as $permission) {
            if ($permission -> getName() === $permissionKey) {
                return true;
            }
        }
        return false;
    }

    private function permissionsFor($userId) {
        if (!isset($this -> cache[$userId])) {
            $db = Db::getDb();
            $st = $db -> prepare(self::PERMS_QUERY);
            $st -> bindParam(':userId', $userId);
            $st -> execute();
            $this -> cache[$userId] = Permission::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
        }
        return $this -> cache[$userId];
    }

    public function ensure($permissionKey, $userId = false) {
        if (!$this -> can($permissionKey, $userId)) {
            $userId = $this -> realUserId($userId);
            Logger::instance() -> warn("User $userId attempted unauthorized operation $permissionKey");
            die("You do not have permission to access this resource.  This attempt has been logged.");
        }
    }

}
?>