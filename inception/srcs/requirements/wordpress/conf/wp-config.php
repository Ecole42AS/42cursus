<?php
define('DB_NAME', 'wordpress');
define('DB_USER', 'wordpress_user');
define('DB_PASSWORD', file_get_contents('/run/secrets/db_password'));
define('DB_HOST', 'mariadb_container');
