#include "ConfigLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

static std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

static TLSMode parseTLSMode(const std::string& modeStr) {
    std::string mode = modeStr;
    std::transform(mode.begin(), mode.end(), mode.begin(), ::toupper);

    if (mode == "PSK") return TLSMode::PSK;
    if (mode == "CERT") return TLSMode::CERT;
    throw std::invalid_argument("Unknown TLS mode: " + modeStr);
}

ServerConfig ConfigLoader::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) throw std::runtime_error("Could not open config file");

    std::unordered_map<std::string, std::string> configMap;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = trim(line.substr(0, eq));
        std::string value = trim(line.substr(eq + 1));
        configMap[key] = value;
    }

    ServerConfig config{};
    config.port = std::stoi(configMap["port"]);
    config.tlsMode = parseTLSMode(configMap["tls_mode"]);
    config.certFile = configMap["certificate_file"];
    config.keyFile = configMap["private_key_file"];

    return config;
}
