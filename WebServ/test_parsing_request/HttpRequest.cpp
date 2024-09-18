#include "HttpRequest.hpp"
#include "HttpRequestException.hpp"

// COPLIEN'S FORM
HttpRequest::HttpRequest() 
    : _method(""), _uri(""), _version("HTTP/1.1"), _headers(), _body(""), _queryParameters(), _isChunked(false), _allowedMethods(initMethods()) {}

HttpRequest::~HttpRequest() {}

HttpRequest::HttpRequest(const HttpRequest& src) 
    : _method(src._method), _uri(src._uri), _version(src._version), _headers(src._headers), _body(src._body), _queryParameters(src._queryParameters), _isChunked(src._isChunked), _allowedMethods(src._allowedMethods) {}

HttpRequest& HttpRequest::operator=(const HttpRequest& src) {
    if (this != &src) {
        _method = src._method;
        _uri = src._uri;
        _version = src._version;
        _headers = src._headers;
        _body = src._body;
        _queryParameters = src._queryParameters;
        _allowedMethods = src._allowedMethods;
        _isChunked = src._isChunked;
    }
    return *this;
}

// 1) REQUEST LINE
std::string HttpRequest::getMethod() const { return _method; }
std::string HttpRequest::getURI() const { return _uri; }
std::string HttpRequest::getHTTPVersion() const { return _version; }

// 2) HEADERS
std::map<std::string, std::string> HttpRequest::getHeaders() const { return _headers; }
std::string HttpRequest::getHeader(const std::string& name) const {
    std::map<std::string, std::string>::const_iterator it = _headers.find(name);
    if (it != _headers.end()) {
        return it->second;
    } else {
        return "";
    }
}

// 3) BODY
std::string HttpRequest::getBody() const { return _body; }
std::map<std::string, std::string> HttpRequest::getQueryParameters() const { return _queryParameters; }

// OTHER
const std::set<std::string> HttpRequest::initMethods() {
    std::set<std::string> methods;
    methods.insert("GET");
    methods.insert("POST");
    methods.insert("DELETE");
    return methods;
}

// Parsing principal
void HttpRequest::parse(const std::string& raw_request) {
    if (!isValidRequest(raw_request)) {
        throw HttpRequestException("Invalid request format: request is not properly formatted.");
    }

    try {
        _method = extractMethod(raw_request);
        _uri = extractURI(raw_request);
        _version = extractHTTPVersion(raw_request);
        _headers = extractHeaders(raw_request);
        if (_method == "POST") {
            _body = extractBody(raw_request);
        } else if (_method == "GET" || _method == "DELETE") {
            if (hasBody(raw_request)) {
                throw HttpRequestException("GET or DELETE request should not contain a body.");
            }
        }
        _isChunked = checkIfChunked();
        _queryParameters = extractQueryParameters(_uri);
    } catch (const HttpRequestException& e) {
        std::cerr << "Error during request parsing: " << e.what() << std::endl;
        clearRequestData();
    }
}

// Fonctions auxiliaires (trim, safe_substr, etc.)
std::string HttpRequest::safe_substr(const std::string& str, size_t start, size_t length) {
    if (start >= str.size()) throw HttpRequestException("Substring extraction failed: start index out of bounds.");
    if (start + length > str.size()) throw HttpRequestException("Substring extraction failed: length out of bounds.");
    return str.substr(start, length);
}

std::string HttpRequest::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return safe_substr(str, first, last - first + 1);
}

bool HttpRequest::isValidRequest(const std::string& raw_request) {
    size_t method_end = raw_request.find(' ');
    size_t uri_end = raw_request.find(' ', method_end + 1);
    size_t version_end = raw_request.find("\r\n", uri_end + 1);
    if (method_end == std::string::npos || uri_end == std::string::npos || version_end == std::string::npos) {
        return false;
    }
    return true;
}

bool HttpRequest::hasBody(const std::string& raw_request) {
    return raw_request.find("\r\n\r\n") != std::string::npos && raw_request.size() > raw_request.find("\r\n\r\n") + 4;
}

void HttpRequest::clearRequestData() {
    _method.clear();
    _uri.clear();
    _queryParameters.clear();
    _version.clear();
    _headers.clear();
    _body.clear();
    _isChunked = false;
}

// Fonctions d'extraction
std::string HttpRequest::extractMethod(const std::string& raw_request) {
    size_t method_end = raw_request.find(' ');
    if (method_end == std::string::npos) throw MissingMethodException();
    return raw_request.substr(0, method_end);
}

std::string HttpRequest::extractURI(const std::string& raw_request) {
    size_t method_end = raw_request.find(' ');
    size_t uri_end = raw_request.find(' ', method_end + 1);
    return safe_substr(raw_request, method_end + 1, uri_end - method_end - 1);
}

std::map<std::string, std::string> HttpRequest::extractHeaders(const std::string& raw_request) {
    std::map<std::string, std::string> headers;
    size_t headers_start = raw_request.find("\r\n") + 2;
    size_t headers_end = raw_request.find("\r\n\r\n", headers_start);
    size_t current = headers_start;
    while (current < headers_end) {
        size_t delimiter = raw_request.find(": ", current);
        size_t end_of_line = raw_request.find("\r\n", current);
        std::string key = raw_request.substr(current, delimiter - current);
        std::string value = raw_request.substr(delimiter + 2, end_of_line - delimiter - 2);
        headers[trim(key)] = trim(value);
        current = end_of_line + 2;
    }
    return headers;
}

std::string HttpRequest::extractBody(const std::string& raw_request) {
    size_t body_start = raw_request.find("\r\n\r\n") + 4;
    return raw_request.substr(body_start);
}

std::string HttpRequest::extractHTTPVersion(const std::string& raw_request) {
    size_t uri_end = raw_request.find(' ', raw_request.find(' ') + 1);
    size_t version_end = raw_request.find("\r\n", uri_end + 1);
    return safe_substr(raw_request, uri_end + 1, version_end - uri_end - 1);
}

bool HttpRequest::checkIfChunked() {
    return _headers.find("Transfer-Encoding") != _headers.end() && _headers["Transfer-Encoding"] == "chunked";
}

bool HttpRequest::isChunked() const {
    return _isChunked;
}

std::map<std::string, std::string> HttpRequest::extractQueryParameters(const std::string& uri) {
    std::map<std::string, std::string> queryParameters;
    size_t query_start = uri.find('?');
    if (query_start != std::string::npos) {
        std::string query_string = uri.substr(query_start + 1);
        size_t param_start = 0;
        while (param_start < query_string.size()) {
            size_t equal_pos = query_string.find('=', param_start);
            size_t ampersand_pos = query_string.find('&', param_start);
            if (ampersand_pos == std::string::npos) ampersand_pos = query_string.size();
            std::string key = query_string.substr(param_start, equal_pos - param_start);
            std::string value = query_string.substr(equal_pos + 1, ampersand_pos - equal_pos - 1);
            queryParameters[trim(key)] = trim(value);
            param_start = ampersand_pos + 1;
        }
    }
    return queryParameters;
}

// Surcharge de l'opérateur << pour afficher la requête
std::ostream& operator<<(std::ostream& os, const HttpRequest& req) {
    os << "Method: " << req.getMethod() << "\n";
    os << "URI: " << req.getURI() << "\n";
    os << "Version: " << req.getHTTPVersion() << "\n";
    os << "Headers: \n";
    std::map<std::string, std::string> headers = req.getHeaders();  // Copie locale des headers
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
        os << "  " << it->first << ": " << it->second << "\n";
    }
    os << "Body: " << req.getBody() << "\n";
    return os;
}

void testRequest(const std::string& raw_request) {
    HttpRequest request;
    try {
        request.parse(raw_request);

        
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

