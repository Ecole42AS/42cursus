#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>

// Fonction utilitaire pour lire une ligne à partir d'un flux
std::string readLine(std::istringstream& stream) {
    std::string line;
    std::getline(stream, line);
    return line;
}

// Fonction utilitaire pour enlever les espaces superflus
std::string trim(const std::string& str) {
    size_t first_non_space = str.find_first_not_of(" \t");
    if (first_non_space == std::string::npos) return "";

    size_t last_non_space = str.find_last_not_of(" \t");
    return str.substr(first_non_space, last_non_space - first_non_space + 1);
}

// Fonction pour extraire la ligne de requête (méthode, URI et version HTTP)
void parseRequestLine(const std::string& line, std::string& method, std::string& uri, std::string& http_version) {
    std::istringstream line_stream(line);
    line_stream >> method >> uri >> http_version;
    if (line_stream.fail()) throw std::runtime_error("Invalid request line format.");
}

// Fonction principale de parsing
void parseHttpRequest(const std::string& raw_request) {
    std::istringstream request_stream(raw_request);
    std::string line;

    // Parse la ligne de requête
    line = readLine(request_stream);
    std::string method, uri, http_version;
    parseRequestLine(line, method, uri, http_version);

    std::cout << "Method: " << method << std::endl;
    std::cout << "URI: " << uri << std::endl;
    std::cout << "HTTP Version: " << http_version << std::endl;

    // Parse les en-têtes
    std::map<std::string, std::string> headers;
    while (true) {
        line = readLine(request_stream);
        if (line == "\r") break; // Fin des en-têtes
        if (line.empty()) continue; // Ignorer les lignes vides

        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) throw std::runtime_error("Invalid header format.");

        std::string key = trim(line.substr(0, colon_pos));
        std::string value = trim(line.substr(colon_pos + 1));

        headers[key] = value;
    }

    std::cout << "Headers:" << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // Parse le corps
    std::string body;
    std::getline(request_stream, body, '\0'); // Lire les données restantes comme corps
    std::cout << "Body: " << body << std::endl;

    // Vérifie si la requête est chunked
    std::map<std::string, std::string>::const_iterator it = headers.find("Transfer-Encoding");
    bool is_chunked = (it != headers.end() && it->second == "chunked");

    if (is_chunked) {
        std::cout << "The request is chunked." << std::endl;
    } else {
        std::cout << "The request is not chunked." << std::endl;
    }
}

// Fonction de test
void testRequest(const std::string& raw_request) {
    try {
        parseHttpRequest(raw_request);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    // Exemple de requête HTTP pour test
    const std::string raw_request = 
		"POST /api/v1/upload HTTP/1.1\r\n"
		"Bi: 123\r\n"
		"Host: www.example.com\r\n"
		"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36\r\n"
		"Accept: application/json\r\n"
		"Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW\r\n"
		"Content-Length: 123\r\n"
		"Authorization: Bearer your_access_token_here\r\n"
		"Cookie: sessionId=abc123; userId=789\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"\r\n"
		"------WebKitFormBoundary7MA4YWxkTrZu0gW\r\n" // pour délimiter les différentes parties des données envoyées dans le body
		"Content-Disposition: form-data; name=\"file\"; filename=\"example.txt\"\r\n"
		"Content-Type: text/plain\r\n"
		"\r\n"
		"This is the content of the file.\r\n"
		"------WebKitFormBoundary7MA4YWxkTrZu0gW--\r\n"
			"Content-Disposition: form-data; name=\"description\"\r\n"
		"\r\n"
		"This is a description for the file.\r\n"
		"------WebKitFormBoundary7MA4YWxkTrZu0gW--\r\n";

    testRequest(raw_request);
    return 0;
}
