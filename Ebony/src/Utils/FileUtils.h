#pragma once

#include <filesystem>
#include <string>

namespace Ebony::FileUtils {

/**
 * @brief Reads the entire contents of a text file and returns it as a string.
 * @param path Path to the file.
 * @return File contents as std::string.
 */
std::string ReadFileAsString(const std::filesystem::path &path);

} // namespace Ebony::FileUtils
