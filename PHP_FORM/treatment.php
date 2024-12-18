<?php
require 'config.php'; // Connexion à la base de données

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $name = trim($_POST['name'] ?? '');
    $email = trim($_POST['email'] ?? '');
    $password = $_POST['password'] ?? '';

    $errors = [];

    // Validation des champs
    if (empty($name)) {
        $errors[] = "Le champ 'Nom' est requis.";
    }

    if (empty($email) || !filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $errors[] = "Veuillez entrer une adresse email valide.";
    }

    if (empty($password) || strlen($password) < 8) {
        $errors[] = "Le mot de passe doit contenir au moins 8 caractères.";
    }

    if ($errors) {
        foreach ($errors as $error) {
            echo "<p>$error</p>";
        }
        exit;
    }

    // Hachage du mot de passe
    $hashedPassword = password_hash($password, PASSWORD_BCRYPT);

    // Insertion des données dans la base de données
    try {
        $stmt = $pdo->prepare("INSERT INTO users (name, email, password) VALUES (:name, :email, :password)");
        $stmt->execute([
            ':name' => $name,
            ':email' => $email,
            ':password' => $hashedPassword
        ]);
        echo "Formulaire soumis avec succès !";
    } catch (PDOException $e) {
        die("Erreur lors de l'insertion des données : " . $e->getMessage());
    }
}
?>
