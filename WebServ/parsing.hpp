#pragma once

#include <string>
#include <iostream>
#include <map>

std::string extractMethod(const std::string& raw_request);
std::string extractURI(const std::string& raw_request);
std::string extractHTTPVersion(const std::string& raw_request);
std::map<std::string, std::string> extractHeaders(const std::string& raw_request);
std::string extractBody(const std::string& raw_request);
bool checkIfChunked(const std::string& raw_request);

