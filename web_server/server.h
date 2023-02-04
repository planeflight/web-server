#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

#include "web_server/response.h"

namespace http {

class Server {
  public:
    Server(uint32_t port = 5000);
    ~Server();

    void run();

    void add_route(const std::string &route, const response::Response &res);

  private:
    void send_route(int client, const std::string &method, const std::string &route);
    void send_resource(int client, const std::string &method, const std::string &resource);

    bool running = true;

    // server and socket
    int sock = 0;
    uint32_t port;

    // routing and requests
    std::unordered_map<std::string, response::Response> routes;
};

} // namespace http

#endif // WEBSERVER_SERVER_H