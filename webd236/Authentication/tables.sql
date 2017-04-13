CREATE TABLE usergroups (
       userId INTEGER NOT NULL,
       groupId INTEGER NOT NULL,
       FOREIGN KEY(userId) REFERENCES users(id) ON DELETE CASCADE,
       FOREIGN KEY(groupId) REFERENCES groups(id) ON DELETE CASCADE
)

CREATE TABLE grouppermissions (
       permissionId INTEGER NOT NULL,
       groupId INTEGER NOT NULL,
       FOREIGN KEY(permissionId) REFERENCES permissions(id) ON DELETE CASCADE,
       FOREIGN KEY(groupId) REFERENCES groups(id) ON DELETE CASCADE
)