#include "FileUtils.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Ebony::FileUtils {

std::string ReadFileAsString(const std::filesystem::path &path) {
    std::ifstream file(path, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "[FileUtils] Failed to open file: " << path << std::endl;
        return {};
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

} // namespace Ebony::FileUtils
