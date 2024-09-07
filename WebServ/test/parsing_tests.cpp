#include <gtest/gtest.h>
#include "../parsing/parsing2.hpp"

// Test pour extractMethod
TEST(ExtractMethodTest, ValidMethods) {
    EXPECT_EQ(extractMethod("GET /index.html HTTP/1.1\r\n\r\n"), "GET");
    EXPECT_EQ(extractMethod("POST /api/v1/resource HTTP/1.1\r\n\r\n"), "POST");
    EXPECT_EQ(extractMethod("PUT /update HTTP/1.1\r\n\r\n"), "PUT");
    EXPECT_EQ(extractMethod("DELETE /delete HTTP/1.1\r\n\r\n"), "DELETE");
}

TEST(ExtractMethodTest, InvalidFormat) {
    // Test pour le cas où la méthode n'est pas spécifiée correctement
    EXPECT_THROW({
        try {
            extractMethod("GET HTTP/1.1\r\n\r\n");
        } catch (const std::runtime_error& e) {
            EXPECT_STREQ("Invalid request format: missing method.", e.what());
            throw;
        }
    }, std::runtime_error);

    EXPECT_THROW({
        try {
            extractMethod("POST /api/v1/resource"); // Pas de version HTTP
        } catch (const std::runtime_error& e) {
            EXPECT_STREQ("Invalid request format: missing method.", e.what());
            throw;
        }
    }, std::runtime_error);
}

// Test pour extractURI
TEST(ExtractURITest, ValidURIs) {
    EXPECT_EQ(extractURI("GET /index.html HTTP/1.1\r\n\r\n"), "/index.html");
    EXPECT_EQ(extractURI("POST /api/v1/resource HTTP/1.1\r\n\r\n"), "/api/v1/resource");
}

TEST(ExtractURITest, InvalidFormat) {
    EXPECT_THROW(extractURI("GET HTTP/1.1\r\n\r\n"), std::runtime_error);
}

// Test pour extractHTTPVersion
TEST(ExtractHTTPVersionTest, ValidVersions) {
    EXPECT_EQ(extractHTTPVersion("GET /index.html HTTP/1.1\r\n\r\n"), "HTTP/1.1");
    EXPECT_EQ(extractHTTPVersion("POST /api/v1/resource HTTP/2.0\r\n\r\n"), "HTTP/2.0");
}

TEST(ExtractHTTPVersionTest, InvalidFormat) {
    EXPECT_THROW(extractHTTPVersion("GET /index.html\r\n\r\n"), std::runtime_error);
}

// Test pour extractHeaders
TEST(ExtractHeadersTest, ValidHeaders) {
    std::map<std::string, std::string> headers = extractHeaders("GET /index.html HTTP/1.1\r\nHost: example.com\r\nUser-Agent: test\r\n\r\n");
    EXPECT_EQ(headers.at("Host"), "example.com");
    EXPECT_EQ(headers.at("User-Agent"), "test");
}

TEST(ExtractHeadersTest, HeadersWithSpaces) {
    std::map<std::string, std::string> headers = extractHeaders("GET /index.html HTTP/1.1\r\n Host : example.com \r\n User-Agent : test \r\n\r\n");
    EXPECT_EQ(headers.at("Host"), "example.com");
    EXPECT_EQ(headers.at("User-Agent"), "test");
}

TEST(ExtractHeadersTest, MissingHeaders) {
    EXPECT_THROW(extractHeaders("GET /index.html HTTP/1.1\r\n\r\n"), std::runtime_error);
}

// Test pour extractBody
TEST(ExtractBodyTest, BodyExtraction) {
    EXPECT_EQ(extractBody("POST /api/v1/upload HTTP/1.1\r\n\r\nThis is the body"), "This is the body");
    EXPECT_EQ(extractBody("POST /api/v1/upload HTTP/1.1\r\nContent-Length: 12\r\n\r\nHello World!"), "Hello World!");
}

TEST(ExtractBodyTest, NoBody) {
    EXPECT_EQ(extractBody("GET /index.html HTTP/1.1\r\n\r\n"), "");
}

// Test pour checkIfChunked
TEST(CheckIfChunkedTest, ChunkedEncoding) {
    std::string request = "POST /upload HTTP/1.1\r\nTransfer-Encoding: chunked\r\n\r\n";
    EXPECT_TRUE(checkIfChunked(request));
}

TEST(CheckIfChunkedTest, NotChunkedEncoding) {
    std::string request = "POST /upload HTTP/1.1\r\nContent-Length: 123\r\n\r\n";
    EXPECT_FALSE(checkIfChunked(request));
}
