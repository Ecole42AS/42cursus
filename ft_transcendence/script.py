import os

def clean_file(file_path):
    """Supprime les lignes vides ou contenant uniquement des espaces blancs, en ne laissant qu'une seule ligne vide consécutive."""
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Filtrer les lignes pour ne laisser qu'une seule ligne vide consécutive
    cleaned_lines = []
    prev_blank = False

    for line in lines:
        if line.strip() == "":
            if not prev_blank:  # Ajouter une seule ligne vide si elle n'est pas précédée par une autre
                cleaned_lines.append("\n")
            prev_blank = True
        else:
            cleaned_lines.append(line)
            prev_blank = False

    # Écrire le contenu nettoyé dans le fichier
    with open(file_path, 'w') as file:
        file.writelines(cleaned_lines)

def process_files(directory):
    """Parcourt tous les fichiers .py dans le répertoire courant et ses sous-répertoires."""
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.py'):
                file_path = os.path.join(root, file)
                print(f"Cleaning: {file_path}")
                clean_file(file_path)

if __name__ == "__main__":
    # Dossier de départ (dossier courant)
    base_directory = os.getcwd()
    process_files(base_directory)

