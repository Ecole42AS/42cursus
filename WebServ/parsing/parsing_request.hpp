#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

// Exceptions personnalisées
class HttpRequestException : public std::runtime_error {
public:
    explicit HttpRequestException(const std::string& message)
        : std::runtime_error(message) {}
};

class MissingBodyException : public HttpRequestException {
public:
    MissingBodyException()
        : HttpRequestException("Invalid request format: missing body.") {}
};

class InvalidQueryStringException : public HttpRequestException {
public:
    InvalidQueryStringException()
        : HttpRequestException("Invalid request format: invalid query string.") {}
};


class MissingMethodException : public HttpRequestException {
public:
    MissingMethodException()
        : HttpRequestException("Invalid request format: missing method.") {}
};

class MissingURIException : public HttpRequestException {
public:
    MissingURIException()
        : HttpRequestException("Invalid request format: missing URI.") {}
};

class MissingHTTPVersionException : public HttpRequestException {
public:
    MissingHTTPVersionException()
        : HttpRequestException("Invalid request format: missing HTTP version.") {}
};

class MissingHeadersException : public HttpRequestException {
public:
    MissingHeadersException()
        : HttpRequestException("Invalid request format: missing headers.") {}
};

class MissingEndOfHeadersException : public HttpRequestException {
public:
    MissingEndOfHeadersException()
        : HttpRequestException("Invalid request format: missing end of headers.") {}
};

class InvalidHeaderFormatException : public HttpRequestException {
public:
    InvalidHeaderFormatException()
        : HttpRequestException("Invalid header format: missing colon or invalid header.") {}
};

class BodyTooLargeException : public HttpRequestException {
public:
    BodyTooLargeException() : HttpRequestException("Request body is too large.") {}
};

// void parse(const std::string& raw_request);
std::string extractMethod(const std::string& raw_request);
std::string extractURI(const std::string& raw_request);
std::map<std::string, std::string> extractQueryParameters(const std::string& uri);
std::string extractHTTPVersion(const std::string& raw_request);
std::map<std::string, std::string> extractHeaders(const std::string& raw_request);
std::string extractBody(const std::string& raw_request);
bool checkIfChunked(const std::string& raw_request);
std::string safe_substr(const std::string& str, size_t start, size_t length);
std::string trim(const std::string& str);
bool isValidRequest(const std::string& raw_request);
void testRequest(const std::string& raw_request);
