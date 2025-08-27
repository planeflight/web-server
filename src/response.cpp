#include "response.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace http::response {

std::string read_file(const std::string &file) {
    // check the type of file
    // if it ends with s, it must be js or css
    std::ifstream f;
    std::string path = file;
    if (file[0] == '/') {
        path = file.substr(1);
    }

    if (file[file.size() - 1] == 's') {
        f.open(static_path + path);
    } else {
        f.open(html_path + path);
    }
    std::stringstream stream;

    std::string line;
    while (std::getline(f, line)) {
        stream << line << '\n';
    }
    return stream.str();
}

} // namespace http::response
