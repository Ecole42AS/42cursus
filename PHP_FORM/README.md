# Commandes pour le projet PHP

## Commandes MySQL

### Créer la base de données et la table
```sql
CREATE DATABASE IF NOT EXISTS testdb;

USE testdb;

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL,
    password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
