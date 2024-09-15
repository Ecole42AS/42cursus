#include "parsing_request.hpp"
#include "HttpRequest.hpp"
const size_t MAX_BODY_SIZE = 2 * 1024 * 1024; // 2 Mo


void HttpRequest::parse(const std::string& raw_request) {
    if (!isValidRequest(raw_request)) {
        throw HttpRequestException("Invalid request format: request is not properly formatted.");
    }

    try {
        setMethod(extractMethod(raw_request));
        setURI(extractURI(raw_request));
        setHTTPVersion(extractHTTPVersion(raw_request));
        setHeaders(extractHeaders(raw_request));
        setBody(extractBody(raw_request));
        setIsChunked(checkIfChunked(raw_request));
        setQueryParameters(extractQueryParameters(_uri));
    } catch (const HttpRequestException& e) {
        std::cerr << "Error during request parsing: " << e.what() << std::endl;
        clearRequestData();
    }
}

void HttpRequest::clearRequestData() {
    _method.clear();
    _uri.clear();
    _query_params.clear();
    _version.clear();
    _headers.clear();
    _body.clear();
    _is_chunked = false;
}
bool isValidRequest(const std::string& raw_request) {
    // Check if the request ends with "\r\n\r\n" for non-chunked requests
    size_t body_start = raw_request.find("\r\n\r\n");
    if (body_start == std::string::npos) {
        // If not found, check for chunked encoding
        std::map<std::string, std::string> headers = extractHeaders(raw_request);
        std::map<std::string, std::string>::const_iterator it = headers.find("Transfer-Encoding");
        if (it != headers.end() && it->second == "chunked") {
            // Chunked encoding should have a valid chunked body format
            return checkIfChunked(raw_request);
        }
        return false; // Invalid if not chunked and "\r\n\r\n" is not found
    }

    // Check the headers part
    std::string headers_part = raw_request.substr(0, body_start);
    
    // Ensure that the headers part ends with "\r\n\r\n"
    // size_t headers_end = headers_part.find("\r\n\r\n");
    // if (headers_end == std::string::npos || headers_end != headers_part.size() - 4) {
    //     return false; // No valid end of headers found
    // }

    // // Check if each line ends with "\r\n"
    // size_t pos = 0;
    // while ((pos = headers_part.find("\r\n", pos)) != std::string::npos) {
    //     if (pos + 2 < headers_part.size()) {
    //         if (headers_part[pos + 2] != '\r' && headers_part[pos + 2] != '\n') {
    //             return false; // Invalid line ending
    //         }
    //         pos += 2;
    //     } else {
    //         return false; // Incomplete line ending
    //     }
    // }

    // Check if the headers part has at least one valid header
    if (headers_part.find(":") == std::string::npos) {
        return false; // No headers found
    }

    // Validate request line (Method URI HTTP-Version)
    size_t method_end = raw_request.find(' ');
    if (method_end == std::string::npos) return false;
    size_t uri_end = raw_request.find(' ', method_end + 1);
    if (uri_end == std::string::npos) return false;
    size_t version_end = raw_request.find("\r\n", uri_end + 1);
    if (version_end == std::string::npos) return false;

    std::string method = raw_request.substr(0, method_end);
    if (method != "GET" && method != "POST" && method != "PUT" && method != "DELETE" && method != "HEAD") {
        return false;
    }

    std::string version = raw_request.substr(uri_end + 1, version_end - uri_end - 1);
    if (version != "HTTP/1.1" && version != "HTTP/1.0" && version != "HTTP/2" && version != "HTTP/3") {
        return false;
    }

    return true;
}


// bool isValidRequest(const std::string& raw_request) {
//     // Check if the request ends with "\r\n\r\n"
//     if (raw_request.size() < 4 || raw_request.substr(raw_request.size() - 4) != "\r\n\r\n") {
//         return false;
//     }

//     // Check if each line ends with "\r\n"
//     size_t pos = 0;
//     while ((pos = raw_request.find("\r\n", pos)) != std::string::npos) {
//         if (pos + 2 < raw_request.size() && raw_request[pos + 2] != '\r' && raw_request[pos + 2] != '\n') {
//             return false; // Invalid line ending
//         }
//         pos += 2;
//     }

//     // Check the method, URI, and HTTP version
//     size_t first_space = raw_request.find(' ');
//     size_t second_space = raw_request.find(' ', first_space + 1);
//     size_t version_end = raw_request.find("\r\n", second_space + 1);

//     if (first_space == std::string::npos || second_space == std::string::npos || version_end == std::string::npos) {
//         return false; 
//     }

//     std::string method = raw_request.substr(0, first_space);
//     if (method != "GET" && method != "POST" && method != "PUT" && method != "DELETE" && method != "HEAD") {
//         return false; 
//     }

//     std::string version = raw_request.substr(second_space + 1, version_end - second_space - 1);
//     if (version != "HTTP/1.1" && version != "HTTP/1.0" && version != "HTTP/2" && version != "HTTP/3") {
//         return false;
//     }

//     return true;
// }

// Fonction utilitaire pour gérer les erreurs d'extraction de sous-chaînes (dépassement de la taille de la chaîne)
std::string safe_substr(const std::string& str, size_t start, size_t length) {
    if (start >= str.size()) {
        throw HttpRequestException("Substring extraction failed: start index out of bounds.");
    }
    if (start + length > str.size()) {
        throw HttpRequestException("Substring extraction failed: length out of bounds.");
    }
    return str.substr(start, length);
}

std::string trim(const std::string& str) {
    size_t first_non_space = str.find_first_not_of(" \t");
    if (first_non_space == std::string::npos) return "";

    size_t last_non_space = str.find_last_not_of(" \t");
    return safe_substr(str, first_non_space, last_non_space - first_non_space + 1);
}

std::string extractMethod(const std::string& raw_request) {
    size_t method_end = raw_request.find(' ');
    if (method_end == std::string::npos) throw MissingMethodException();
    return raw_request.substr(0, method_end);
}

std::string extractURI(const std::string& raw_request) {
    size_t method_end = raw_request.find(' ');
    if (method_end == std::string::npos) throw MissingMethodException();

    size_t uri_end = raw_request.find(' ', method_end + 1);
    if (uri_end == std::string::npos) throw MissingURIException();

    std::string uri = safe_substr(raw_request, method_end + 1, uri_end - method_end - 1);
    if (uri.empty()) throw MissingURIException();

    return uri;
}

std::map<std::string, std::string> extractQueryParameters(const std::string& uri) {
    std::map<std::string, std::string> query_params;
    size_t query_start = uri.find('?');
    if (query_start == std::string::npos) return query_params; // Pas de paramètres de requête

    std::string query_string = uri.substr(query_start + 1);
    size_t param_start = 0;

    while (param_start < query_string.size()) {
        size_t param_end = query_string.find('&', param_start);
        if (param_end == std::string::npos) param_end = query_string.size();

        std::string param = query_string.substr(param_start, param_end - param_start);
        size_t equal_pos = param.find('=');

        if (equal_pos == std::string::npos) {
            throw InvalidQueryStringException(); // Paramètre sans égal
        }

        std::string key = trim(param.substr(0, equal_pos));
        std::string value = trim(param.substr(equal_pos + 1));

        query_params[key] = value;
        param_start = param_end + 1;
    }

    return query_params;
}


std::string extractHTTPVersion(const std::string& raw_request) {
    size_t uri_end = raw_request.find(' ', raw_request.find(' ') + 1);
    if (uri_end == std::string::npos) throw MissingURIException();

    size_t version_end = raw_request.find("\r\n", uri_end + 1);
    if (version_end == std::string::npos) throw MissingHTTPVersionException();

    return safe_substr(raw_request, uri_end + 1, version_end - uri_end - 1);
}

std::map<std::string, std::string> extractHeaders(const std::string& raw_request) {
    std::map<std::string, std::string> headers;
    size_t headers_start = raw_request.find("\r\n");
    if (headers_start == std::string::npos) throw MissingHeadersException();
    headers_start += 2;  // Skip \r\n

    size_t headers_end = raw_request.find("\r\n\r\n", headers_start);
    if (headers_end == std::string::npos) throw MissingEndOfHeadersException();

    size_t current = headers_start;
    while (current < headers_end) {
        size_t line_end = raw_request.find("\r\n", current);
        if (line_end == std::string::npos || line_end > headers_end) break;

        size_t colon_pos = raw_request.find(':', current);
        if (colon_pos == std::string::npos || colon_pos > line_end) {
            throw InvalidHeaderFormatException();
        }

        std::string key = safe_substr(raw_request, current, colon_pos - current);
        std::string value = safe_substr(raw_request, colon_pos + 2, line_end - colon_pos - 2);  // +2 to skip ": "

        key = trim(key);
        value = trim(value);

        if (key.empty()) throw InvalidHeaderFormatException();

        headers[key] = value;
        current = line_end + 2;
    }

    return headers;
}


std::string extractBody(const std::string& raw_request) {
    size_t body_start = raw_request.find("\r\n\r\n");
    if (body_start == std::string::npos) return ""; // Pas de corps présent

    std::string body = safe_substr(raw_request, body_start + 4, std::string::npos);
    if (body.size() > MAX_BODY_SIZE) {
        throw BodyTooLargeException();
    }

    return body;
}

/* aide à déterminer le mode de transfert des données dans une requête HTTP(en morceaux ou non), 
permettant au serveur de gérer correctement les données reçues.*/
// bool checkIfChunked(const std::string& raw_request) {
//     std::map<std::string, std::string> headers = extractHeaders(raw_request);
//     std::map<std::string, std::string>::const_iterator it = headers.find("Transfer-Encoding");
//     if (it == headers.end()) return false;
//     std::string encoding = trim(it->second);

//     return encoding == "chunked";
// }

bool checkIfChunked(const std::string& raw_request) {
    // Extract headers
    std::map<std::string, std::string> headers = extractHeaders(raw_request);
    std::map<std::string, std::string>::const_iterator it = headers.find("Transfer-Encoding");
    if (it == headers.end()) return false;
    
    std::string encoding = trim(it->second);
    if (encoding != "chunked") return false;

    // Extract and validate chunked data
    size_t body_start = raw_request.find("\r\n\r\n");
    if (body_start == std::string::npos) return false; // No body found

    std::string body = raw_request.substr(body_start + 4);
    size_t pos = 0;
    bool valid = true;

    while (pos < body.size()) {
        // Find the end of the chunk size line
        size_t chunk_size_end = body.find("\r\n", pos);
        if (chunk_size_end == std::string::npos) {
            valid = false;
            break;
        }

        // Extract and convert chunk size
        std::string chunk_size_str = body.substr(pos, chunk_size_end - pos);
        int chunk_size = 0;
        for (size_t i = 0; i < chunk_size_str.size(); ++i) {
            char c = chunk_size_str[i];
            if (c >= '0' && c <= '9') {
                chunk_size = (chunk_size << 4) + (c - '0');
            } else if (c >= 'a' && c <= 'f') {
                chunk_size = (chunk_size << 4) + (c - 'a' + 10);
            } else if (c >= 'A' && c <= 'F') {
                chunk_size = (chunk_size << 4) + (c - 'A' + 10);
            } else {
                valid = false;
                break;
            }
        }

        if (!valid) break;

        // Check for zero-sized chunk
        if (chunk_size == 0) {
            pos = chunk_size_end + 2;
            if (pos != body.size()) {
                valid = false;
            }
            break;
        }

        // Move past the chunk data
        pos = chunk_size_end + 2 + chunk_size;
        if (pos > body.size()) {
            valid = false;
            break;
        }
    }

    return valid;
}

// Fonction de test pour vérifier le parsing de la requête
void testRequest(const std::string& raw_request) {
    HttpRequest request;
    try {
        request.parse(raw_request);

        // Vérifiez les données après parsing
        std::cout << "Method: " << request.getMethod() << std::endl;
        std::cout << "URI: " << request.getURI() << std::endl;
        std::cout << "HTTP Version: " << request.getHTTPVersion() << std::endl;
        std::cout << "Headers:" << std::endl;

        std::map<std::string, std::string> headers = request.getHeaders();
        for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }

        std::cout << "Body: " << request.getBody() << std::endl;

        if (request.isChunked()) {
            std::cout << "The request is chunked." << std::endl;
        } else {
            std::cout << "The request is not chunked." << std::endl;
        }

    } catch (const HttpRequestException& e) {
        std::cerr << "Error during request parsing: " << e.what() << std::endl;
    }
}

//g++ -std=c++98 -Werror -Wall -Wextra parsing_request.cpp main.cpp -o parsing