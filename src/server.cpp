#include "server.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

#include "request.h"
#include "response.h"

namespace http {

Server::Server(uint32_t port) : port(port) {
    // create new socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cout << "Error creating connection\n";
        running = false;
        return;
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port =
        htons(this->port); // store the port in network byte order
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    // bind socket
    int res = bind(sock, (sockaddr *)&server_address, sizeof(server_address));
    if (res < 0) {
        std::cout << "Error binding socket\n";
        running = false;
        return;
    }

    // listen for connections
    res = listen(sock, 8);
    if (res < 0) {
        std::cout << "Error listening with HTTP server\n";
        running = false;
        return;
    }
    std::cout << "HTTP Server is listening on port: " << port << "\n";
}

Server::~Server() {}

void Server::run() {
    if (!running) return;
    std::cout << "Server is running!\n";

    // store the request data in message
    uint32_t message_size = 4096;
    char *message = new char[message_size];
    message[message_size - 1] = '\0';

    while (running) {
        int client_socket = accept(sock, nullptr, nullptr);
        if (client_socket < 0) {
            std::cout << "Error establishing connection with client\n";
            continue;
        }
        read(client_socket, message, message_size - 1);

        // parse message
        std::string method, route;
        request::parse(message, method, route);

        // check if a resource or route
        response::type type = response::parse_route_path(route);
        if (type == response::route) {
            send_route(client_socket, method, route);
        } else {
            send_resource(client_socket, method, route);
        }
        close(client_socket);
    }

    delete[] message;
}

void Server::add_route(const std::string &route,
                       const response::Response &res) {
    routes[route] = res;
}

void Server::send_route(int client,
                        const std::string &method,
                        const std::string &route) {
    // get the Response
    response::Response response = nullptr;
    for (auto &pair : routes) {
        if (pair.first == route) {
            response = pair.second;
            break;
        }
    }

    // check if a response was found
    std::string response_str;
    if (response == nullptr) {
        response_str = "Access Denied: The route is invalid";
    } else {
        response_str = response(method);
    }

    std::stringstream response_stream;
    response_stream << "HTTP/1.1 200 OK\r\n\r\n" << response_str << "\r\n\r\n";
    std::string out = response_stream.str();

    send(client, out.c_str(), out.size(), 0);
}

void Server::send_resource(int client,
                           const std::string &method,
                           const std::string &resource) {
    (void)method;

    std::string response = http::response::read_file(resource);

    std::stringstream response_stream;
    response_stream << "HTTP/1.1 200 OK\r\n\r\n" << response << "\r\n\r\n";
    std::string out = response_stream.str();

    send(client, out.c_str(), out.size(), 0);
}

} // namespace http
