#ifndef REQUEST_H
#define REQUEST_H

#include <string.h>

#include <string>
#include <vector>

namespace http::request {

const std::string post = "POST";
const std::string get = "GET";
const std::string put = "PUT";
const std::string patch = "PATCH";
const std::string del = "DELETE";

inline void parse(char *req, std::string &http_method, std::string &route) {
    static constexpr char delimeter[] = " ";

    // output vector
    std::vector<std::string> split_by_space;
    split_by_space.reserve(2);

    // split the request by space
    char *piece = strtok(req, delimeter);
    size_t i = 0;

    while (piece != nullptr || i < split_by_space.size()) {
        split_by_space.push_back(std::string(piece));
        piece = strtok(nullptr, delimeter);
        ++i;
    }

    // method
    http_method = split_by_space[0];
    route = split_by_space[1];
}

} // namespace http::request

#endif // REQUEST_H
