#include "Save.h"

void Save::SaveData(const char* path, std::vector<std::pair<std::string, std::string>> data, bool rewrite) {
    std::ofstream file;
    if (rewrite) {
        file.open(path, std::ios::out);
    }
    else {
        file.open(path, std::ios::out | std::ios::app);
    }

    if (file.is_open()) {
        for (const auto& pair : data) {
            file << pair.first << "=" << pair.second << "\n";
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << path << std::endl;
    }
}

std::vector<std::pair<std::string, std::string>> Save::LoadData(const char* path) {
    std::vector<std::pair<std::string, std::string>> data;
    std::ifstream file(path);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                data.emplace_back(key, value);
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << path << std::endl;
    }

    return data;
}
