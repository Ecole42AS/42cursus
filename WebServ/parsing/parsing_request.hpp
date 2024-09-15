#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

std::string extractMethod(const std::string& raw_request);
std::string extractURI(const std::string& raw_request);
std::string extractHTTPVersion(const std::string& raw_request);
std::map<std::string, std::string> extractHeaders(const std::string& raw_request);
std::string extractBody(const std::string& raw_request);
bool checkIfChunked(const std::string& raw_request);
std::string safe_substr(const std::string& str, size_t start, size_t length);
std::string trim(const std::string& str);
void testRequest(const std::string& raw_request);

