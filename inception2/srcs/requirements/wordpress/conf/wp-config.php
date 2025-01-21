<?php
// define('DB_NAME', 'wordpress');
// define('DB_USER', 'wordpress_user');
// define('DB_PASSWORD', file_get_contents('/run/secrets/db_password'));
// define('DB_HOST', 'mariadb');
define('DB_NAME', getenv('WORDPRESS_DB_NAME') ?: 'wordpress');
define('DB_USER', getenv('WORDPRESS_DB_USER') ?: 'wordpress_user');
define('DB_PASSWORD', trim(file_get_contents('/run/secrets/db_password')));
define('DB_HOST', getenv('WORDPRESS_DB_HOST') ?: 'mariadb');
