#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include "parsing/parsing2.hpp"

// Fonction utilitaire pour gérer les erreurs d'extraction de sous-chaînes
std::string safe_substr(const std::string& str, size_t start, size_t length) {
    if (start >= str.size()) return "";
    if (start + length > str.size()) length = str.size() - start;
    return str.substr(start, length);
}


// Fonction utilitaire pour enlever les espaces de début et de fin
std::string trim(const std::string& str) {
    size_t first_non_space = str.find_first_not_of(" \t");
    if (first_non_space == std::string::npos) return ""; // La chaîne est entièrement vide ou composée d'espaces

    size_t last_non_space = str.find_last_not_of(" \t");
    return safe_substr(str, first_non_space, last_non_space - first_non_space + 1);
}

Extraction de la méthode HTTP
std::string extractMethod(const std::string& raw_request) {
    size_t method_end = raw_request.find(' ');
    if (method_end == std::string::npos) throw std::runtime_error("Invalid request format: missing method.");
    return raw_request.substr(0, method_end);
}


// Extraction de l'URI
std::string extractURI(const std::string& raw_request) {
    size_t method_end = raw_request.find(' ');
    if (method_end == std::string::npos) throw std::runtime_error("Invalid request format: missing method.");

    size_t uri_end = raw_request.find(' ', method_end + 1);
    if (uri_end == std::string::npos) throw std::runtime_error("Invalid request format: missing URI.");

    return safe_substr(raw_request, method_end + 1, uri_end - method_end - 1);
}

// Extraction de la version HTTP
std::string extractHTTPVersion(const std::string& raw_request) {
    size_t uri_end = raw_request.find(' ', raw_request.find(' ') + 1);
    if (uri_end == std::string::npos) throw std::runtime_error("Invalid request format: missing URI or version.");

    size_t version_end = raw_request.find("\r\n", uri_end + 1);
    if (version_end == std::string::npos) throw std::runtime_error("Invalid request format: missing HTTP version.");

    return safe_substr(raw_request, uri_end + 1, version_end - uri_end - 1);
}

// Extraction des en-têtes HTTP
std::map<std::string, std::string> extractHeaders(const std::string& raw_request) {
    std::map<std::string, std::string> headers;
    size_t headers_start = raw_request.find("\r\n");
    if (headers_start == std::string::npos) throw std::runtime_error("Invalid request format: missing headers.");
    headers_start += 2;  // Passer les caractères \r\n

    size_t headers_end = raw_request.find("\r\n\r\n", headers_start);
    if (headers_end == std::string::npos) throw std::runtime_error("Invalid request format: missing end of headers.");

    size_t current = headers_start;
    while (current < headers_end) {
        size_t line_end = raw_request.find("\r\n", current);
        if (line_end == std::string::npos || line_end > headers_end) break;

        size_t colon_pos = raw_request.find(':', current);
        if (colon_pos == std::string::npos || colon_pos > line_end) throw std::runtime_error("Invalid header format: missing colon.");

        std::string key = safe_substr(raw_request, current, colon_pos - current);
        std::string value = safe_substr(raw_request, colon_pos + 2, line_end - colon_pos - 2);  // +2 to skip ": "

        // Utiliser la fonction trim pour enlever les espaces
        key = trim(key);
        value = trim(value);

        headers[key] = value;
        current = line_end + 2;  // Passer au début de la ligne suivante
    }

    return headers;
}

// Extraction du corps de la requête
std::string extractBody(const std::string& raw_request) {
    size_t body_start = raw_request.find("\r\n\r\n");
    if (body_start == std::string::npos) return ""; // Pas de corps présent
    return safe_substr(raw_request, body_start + 4, std::string::npos);
}

// Vérifier si la requête utilise le transfert par morceaux (chunked)
bool checkIfChunked(const std::string& raw_request) {
    std::map<std::string, std::string> headers = extractHeaders(raw_request);
    std::map<std::string, std::string>::const_iterator it = headers.find("Transfer-Encoding");
    if (it == headers.end()) return false;
    std::string encoding = it->second;
    // Trim any extra whitespace
    encoding = trim(encoding);
    return encoding == "chunked";
}

// int main() {
//     try {
//         const std::string raw_request = 
//             "POST /api/v1/upload HTTP/1.1\r\n"
//             "Bi: 123\r\n"
//             "Host: www.example.com\r\n"
//             "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36\r\n"
//             "Accept: application/json\r\n"
//             "Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW\r\n"
//             "Content-Length: 123\r\n"
//             "Authorization: Bearer your_access_token_here\r\n"
//             "Cookie: sessionId=abc123; userId=789\r\n"
//             "Accept-Encoding: gzip, deflate\r\n"
//             "\r\n"
//             "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\n"
//             "Content-Disposition: form-data; name=\"file\"; filename=\"example.txt\"\r\n"
//             "Content-Type: text/plain\r\n"
//             "\r\n"
//             "This is the content of the file.\r\n"
//             "------WebKitFormBoundary7MA4YWxkTrZu0gW--\r\n";

//         std::string method = extractMethod(raw_request);
//         std::string uri = extractURI(raw_request);
//         std::string http_version = extractHTTPVersion(raw_request);
//         std::map<std::string, std::string> headers = extractHeaders(raw_request);
//         std::string body = extractBody(raw_request);

//         std::cout << "Method: " << method << std::endl;
//         std::cout << "URI: " << uri << std::endl;
//         std::cout << "HTTP Version: " << http_version << std::endl;
//         std::cout << "Headers:" << std::endl;
//         for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
//             std::cout << it->first << ": " << it->second << std::endl;
//         }
//         std::cout << "Body: " << body << std::endl;
        
//         // Check if the request is chunked
//         if (checkIfChunked(raw_request)) {
//             std::cout << "The request is chunked." << std::endl;
//         } else {
//             std::cout << "The request is not chunked." << std::endl;
//         }
//     } catch (const std::runtime_error& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }
