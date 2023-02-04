#include "web_server/request.h"
#include "web_server/response.h"
#include "web_server/server.h"

#include <iostream>

auto main() -> int {
    http::Server *app = new http::Server(8080);

    http::response::set_html_path("public/html/");
    http::response::set_static_path("public/static/");

    app->add_route("/index", [](const std::string &request) -> std::string {
        if (request == http::request::get) {
            return http::response::read_file("index.html");
        }
        return "FAILURE";
    });

    app->add_route("/about", [](const std::string &request) -> std::string {
        if (request == http::request::get) {
            return http::response::read_file("about.html");
        }
        return "FAILURE";
    });

    app->run();
    delete app;

    return 0;
}