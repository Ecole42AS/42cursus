#include <iostream>
#include <fstream>
#include <string>

void replaceString(std::string& source, const std::string& s1, const std::string& s2) {
    size_t pos = 0;
    while ((pos = source.find(s1, pos)) != std::string::npos) {
        source.erase(pos, s1.length());
        source.insert(pos, s2);
        pos += s2.length();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Cannot open file " << filename << "\n";
        return 1;
    }

	//crée une instance(ou objet) de la classe ofstream qui permet d'écrire dans le fichier newFilename (file qui est créer grace a l objet)
    std::string newFilename = filename + ".replace";
    std::ofstream outputFile(newFilename);
    if (!outputFile) 
	{
        std::cerr << "Error: Cannot create file " << newFilename << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        replaceString(line, s1, s2);
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
