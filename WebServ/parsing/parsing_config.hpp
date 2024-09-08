#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>

class Config {
private:
    std::map<std::string, std::string> _server_config; // Paramètres globaux du serveur
    std::map<std::string, std::map<std::string, std::string> > _location_configs; // Configurations par location

    std::string trim(const std::string& str);
	void parseServerDirective(const std::string& line);
	void parseLocation(const std::string& line);
	void parseLocationDirective(const std::string& line);
public:
    Config();
    void parseConfigFile(const std::string& filename);
	std::map<std::string, std::string> getServerConfig() const;
	std::map<std::string, std::string> getLocationConfig(const std::string& path) const;
};
