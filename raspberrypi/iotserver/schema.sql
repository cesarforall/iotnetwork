DROP TABLE IF EXISTS user;
DROP TABLE IF EXISTS device;
DROP TABLE IF EXISTS sensor;
DROP TABLE IF EXISTS sensor_type;
DROP TABLE IF EXISTS sensor_sensor_type;
DROP TABLE IF EXISTS measurements;

CREATE TABLE user (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
);

CREATE TABLE device (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    location TEXT,
    FOREIGN KEY (user_id) REFERENCES user (id) ON DELETE CASCADE
);

CREATE TABLE sensor (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    device_id INTEGER,
    name TEXT,
    FOREIGN KEY (device_id) REFERENCES device (id)
);

CREATE TABLE sensor_type (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT
);

CREATE TABLE sensor_sensor_type (
    sensor_id INTEGER,
    sensor_type_id INTEGER,
    PRIMARY KEY (sensor_id, sensor_type_id),
    FOREIGN KEY (sensor_id) REFERENCES sensor (id) ON DELETE CASCADE,
    FOREIGN KEY (sensor_type_id) REFERENCES sensor_type (id) ON DELETE CASCADE
);

CREATE TABLE measurements (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sensor_id INTEGER,
    sensor_type_id INTEGER,
    value REAL,
    timestamp DATETIME NOT NULL,
    FOREIGN KEY (sensor_id) REFERENCES sensor (id) ON DELETE CASCADE,
    FOREIGN KEY (sensor_type_id) REFERENCES sensor_type (id) ON DELETE CASCADE,
    UNIQUE (sensor_id, sensor_type_id, timestamp)
)