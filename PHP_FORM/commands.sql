-- ===========================================
-- Créer la base de données si elle n'existe pas
-- ===========================================

CREATE DATABASE IF NOT EXISTS testdb;

-- Utiliser la base de données
USE testdb;

-- Créer une table pour les utilisateurs
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL,
    password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Insérer des données dans la table users
INSERT INTO users (name, email, password)
VALUES 
    ('Alice', 'alice@example.com', 'hashedpassword123'),
    ('Bob', 'bob@example.com', 'securepassword456');

-- Afficher toutes les données de la table users
SELECT * FROM users;

-- Mettre à jour un utilisateur
UPDATE users
SET email = 'alice.updated@example.com'
WHERE name = 'Alice';

-- Supprimer un utilisateur spécifique
DELETE FROM users
WHERE name = 'Bob';

-- Supprimer une table
DROP TABLE IF EXISTS users;

-- Supprimer une base de données
DROP DATABASE IF EXISTS testdb;

-- ===========================================
-- Ajout de la base de données "company" et table "employees"
-- ===========================================

-- Créer la base de données "company" si elle n'existe pas
CREATE DATABASE IF NOT EXISTS company;

-- Utiliser la base de données "company"
USE company;

-- Créer une table pour les employés
CREATE TABLE employees (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE,
    department VARCHAR(50),
    salary DECIMAL(10, 2),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Insérer des données dans la table employees
INSERT INTO employees (name, email, department, salary)
VALUES 
    ('Alice', 'alice@example.com', 'HR', 45000.00),
    ('Bob', 'bob@example.com', 'IT', 60000.00),
    ('Charlie', 'charlie@example.com', 'Finance', 55000.00);

-- Afficher toutes les données de la table employees
SELECT * FROM employees;

-- Sélectionner les employés d'un département spécifique
SELECT name, email, salary
FROM employees
WHERE department = 'IT';

-- Mettre à jour le salaire des employés
UPDATE employees
SET salary = salary * 1.10
WHERE department = 'Finance';

-- Supprimer les employés avec un salaire inférieur à 50,000
DELETE FROM employees
WHERE salary < 50000;

-- Ajouter une nouvelle colonne "hire_date" à la table employees
ALTER TABLE employees
ADD COLUMN hire_date DATE;

-- Modifier une colonne existante (changer le type ou ajouter une contrainte)
ALTER TABLE employees
MODIFY COLUMN department VARCHAR(100) NOT NULL;

-- Renommer une colonne existante
ALTER TABLE employees
CHANGE COLUMN department dept_name VARCHAR(100);

-- Supprimer une colonne de la table employees
ALTER TABLE employees
DROP COLUMN hire_date;

-- Créer une table pour les départements
CREATE TABLE departments (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL
);

-- Insérer des données dans la table departments
INSERT INTO departments (id, name)
VALUES 
    (1, 'HR'),
    (2, 'IT'),
    (3, 'Finance');

-- Faire une jointure entre employees et departments
SELECT employees.name AS employee_name, employees.email, employees.salary, departments.name AS department_name
FROM employees
JOIN departments
ON employees.department = departments.name;

-- Supprimer la table "employees"
DROP TABLE IF EXISTS employees;

-- Supprimer la table "departments"
DROP TABLE IF EXISTS departments;

-- Supprimer la base de données "company"
DROP DATABASE IF EXISTS company;

-- ===========================================
-- Commandes d'analyse et d'agrégation
-- ===========================================

-- Trouver le nombre total d'employés
SELECT COUNT(*) AS total_employees
FROM employees;

-- Trouver le salaire moyen par département
SELECT department, AVG(salary) AS average_salary
FROM employees
GROUP BY department;

-- Trier les employés par salaire décroissant
SELECT name, salary
FROM employees
ORDER BY salary DESC;

-- Limiter les résultats (Top 3 employés les mieux payés)
SELECT name, salary
FROM employees
ORDER BY salary DESC
LIMIT 3;
