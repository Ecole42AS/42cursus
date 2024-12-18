<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&display=swap" rel="stylesheet">
    <title>PHP form</title>
    <style>
        input {
            margin-bottom: 10px;
        }
    </style>
</head>
<body>
    <form id="customForm" action="treatment.php" method="POST" novalidate>
        <label for="name">Nom :</label>
        <input type="text" id="name" name="name" required placeholder="Votre nom">
        <span id="nameError" class="error"></span>
        <br><br>

        <label for="email">Email :</label>
        <input type="email" id="email" name="email" required placeholder="Votre email">
        <span id="emailError" class="error"></span>
        <br><br>

        <label for="password">Mot de passe :</label>
        <input type="password" id="password" name="password" required minlength="8" placeholder="Votre mot de passe">
        <span id="passwordError" class="error"></span>
        <br><br>

        <button type="submit">Envoyer</button>
    </form>
</body>
</html>
<script>
    document.getElementById('customForm').addEventListener('submit', function(event) {
        let isValid = true;

        const nameField = document.getElementById('name');
        const emailField = document.getElementById('email');
        const passwordField = document.getElementById('password');

        const nameError = document.getElementById('nameError');
        const emailError = document.getElementById('emailError');
        const passwordError = document.getElementById('passwordError');

        // Réinitialiser les messages d'erreur
        nameError.textContent = '';
        emailError.textContent = '';
        passwordError.textContent = '';

        // Validation du nom
        if (nameField.value.trim() === '') {
            nameError.textContent = 'Veuillez entrer votre nom.';
            isValid = false;
        }

        // Validation de l'email
        if (!emailField.validity.valid) {
            emailError.textContent = 'Veuillez entrer une adresse email valide.';
            isValid = false;
        }

        // Validation du mot de passe
        if (passwordField.value.length < 8) {
            passwordError.textContent = 'Le mot de passe doit contenir au moins 8 caractères.';
            isValid = false;
        }

        if (!isValid) {
            event.preventDefault();
        }
    });
</script>