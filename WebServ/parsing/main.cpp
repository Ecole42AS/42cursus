#include "parsing_request.hpp"

void testRequest(const std::string& raw_request);

int main() {
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