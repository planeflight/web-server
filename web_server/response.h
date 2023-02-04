#ifndef WEBSERVER_RESPONSE_H
#define WEBSERVER_RESPONSE_H

#include <functional>
#include <string.h>
#include <string>
#include <vector>

namespace http::response {

using Response = std::function<std::string(const std::string &)>;

static std::string html_path = "public/html/";
static std::string static_path = "public/static/";

inline void set_html_path(const std::string &path) {
    html_path = path;
}

inline void set_static_path(const std::string &path) {
    static_path = path;
}

std::string read_file(const std::string &file);

enum type {
    resource = 0,
    route = 1
};

/**
 * @param str the path to parse
 * @returns if the route path wants direct access to a resource, or if it wants to call a callback (ie a route)
 */
inline type parse_route_path(const std::string &str) {
    // if there is a . in the path, it must be a resource
    for (const auto &c : str) {
        if (c == '.') {
            return resource;
        }
    }
    return route;
}

} // namespace http::response

#endif // WEBSERVER_RESPONSE_H