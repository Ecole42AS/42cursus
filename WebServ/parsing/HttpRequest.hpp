#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include <iostream>
#include <map>
#include <vector>
#include <set>

// Gère l'analyse et la représentation d'une requête HTTP.
class HttpRequest {
    private:
        std::string _method;
        std::string _uri;
        std::string _version;
		std::map<std::string, std::string> _query_params;
        std::map<std::string, std::string> _headers;
        std::set<std::string> _allowedMethods;
        std::string _body;
        bool _is_chunked;
        
    public:
        HttpRequest();
        ~HttpRequest();
        HttpRequest(const HttpRequest& src);
        HttpRequest& operator=(const HttpRequest& src);

         // Getters
        std::string getMethod() const;
        std::string getURI() const;
        std::string getHTTPVersion() const;
        std::map<std::string, std::string> getHeaders() const;
        std::string getHeader(const std::string& name) const; // check here
        std::string getBody() const;
        bool isChunked() const;

        // Setter (si nécessaire pour simuler des données)
        void setMethod(const std::string& method);
        void setURI(const std::string& uri);
        void setHTTPVersion(const std::string& version);
        void setHeaders(const std::map<std::string, std::string>& headers);
        void setBody(const std::string& body);
        void setIsChunked(bool is_chunked);
		void setQueryParameters(const std::map<std::string, std::string>& query_params);

        // Other Methods
        void parse(const std::string& rawRequest);
        std::set<std::string> initMethods();
        bool isMethodAllowed(const std::string& method) const;
};

std::ostream&	operator<<(std::ostream& os, const HttpRequest& re);

#endif