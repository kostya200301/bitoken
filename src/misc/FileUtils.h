//
// Created by Константин Беляков on 15.12.2024.
//

#ifndef BITOCEN_FILEUTILS_H
#define BITOCEN_FILEUTILS_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class FileUtils {
public:
    /**
     * @brief Reads the entire content of a file and returns it as a string.
     *
     * @param filepath Path to the file to read.
     * @return A string containing the contents of the file.
     * @throws std::runtime_error If the file cannot be opened.
     */
    static std::string readCqlFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл: " + filepath);
        }
        std::stringstream buffer;
        buffer << file.rdbuf(); // Read the entire file into a stringstream
        return buffer.str();
    }
};

#endif //BITOCEN_FILEUTILS_H
