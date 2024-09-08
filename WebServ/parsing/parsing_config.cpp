#include "parsing_config.hpp"

Config::Config() {}


std::map<std::string, std::string> Config::getServerConfig() const {
	return _server_config;
}

std::map<std::string, std::string> Config::getLocationConfig(const std::string& path) const {
	return _location_configs.at(path);
}

void Config::parseConfigFile(const std::string& filename) {
	std::ifstream config_file(filename);
	if (!config_file.is_open()) {
		throw std::runtime_error("Failed to open config file: " + filename);
	}

	std::string line;
	std::string current_section;

	while (std::getline(config_file, line)) {
		line = trim(line);  // Supprimer les espaces inutiles

		// Ignorer les lignes vides ou les commentaires
		if (line.empty() || line[0] == '#') continue;

		// Détection des blocs "server" ou "location"
		if (line == "server {") {
			current_section = "server";
		} else if (line.find("location") == 0) {
			current_section = "location";
			parseLocation(line);
		} else if (line == "}") {
			current_section.clear();
		} else if (current_section == "server") {
			parseServerDirective(line);
		} else if (current_section == "location") {
			parseLocationDirective(line);
		}
	}

	config_file.close();
}

std::string Config::trim(const std::string& str) {
	size_t first = str.find_first_not_of(" \t");
	if (first == std::string::npos) return "";
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, (last - first + 1));
}

void Config::parseServerDirective(const std::string& line) {
	size_t space_pos = line.find(' ');
	if (space_pos == std::string::npos) return;

	std::string key = line.substr(0, space_pos);
	std::string value = trim(line.substr(space_pos + 1));
	_server_config[key] = value;
}

void Config::parseLocation(const std::string& line) {
	size_t space_pos = line.find(' ');
	size_t brace_pos = line.find('{');
	if (space_pos == std::string::npos || brace_pos == std::string::npos) return;

	std::string location_path = trim(line.substr(space_pos, brace_pos - space_pos));
	location_configs_[location_path] = std::map<std::string, std::string>();
}

void Config::parseLocationDirective(const std::string& line) {
	size_t space_pos = line.find(' ');
	if (space_pos == std::string::npos) return;

	std::string key = line.substr(0, space_pos);
	std::string value = trim(line.substr(space_pos + 1));

	// Assigner le dernier emplacement ajouté dans _location_configs
	if (!location_configs_.empty()) {
		location_configs_.rbegin()->second[key] = value;
	}
}

int main() {
    try {
        Config config;
        config.parseConfigFile("server.conf");

        // Afficher les informations générales du serveur
        std::map<std::string, std::string> server_config = config.getServerConfig();
        for (const auto& kv : server_config) {
            std::cout << kv.first << ": " << kv.second << std::endl;
        }

        // Afficher la configuration d'une location spécifique
        std::map<std::string, std::string> location_config = config.getLocationConfig("/images/");
        for (const auto& kv : location_config) {
            std::cout << kv.first << ": " << kv.second << std::endl;
        }

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
