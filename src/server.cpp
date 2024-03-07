#include "server.h"

void Server::bind_server(int argc, char **argv) {
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (argc < 2) {
    throw std::invalid_argument("Need port");
  }
  if (server_socket < 0) {
    throw std::invalid_argument("Error with creating a socket");
  }
  std::cout << "Socket created\n";
  port = atoi(argv[1]);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port);
  ret_bind = bind(server_socket, (struct sockaddr *)&server_address,
                  sizeof(server_address));
  if (ret_bind < 0) {
    throw std::invalid_argument("Error with bind");
  }
  std::cout << "Bind done\n";
  listen(server_socket, SOMAXCONN);
}

void Server::start() {
  char buffer[BUF_SIZE];
  pid_t childpid;
  memset(&server_address, 0, sizeof(server_address));
  while (1) {
    socklen_t len = sizeof(server_address);
    int newserver_socket =
        accept(server_socket, (struct sockaddr *)&server_address, &len);
    if (newserver_socket < 0) {
      printf("Error accepting connection!\n");
      throw std::invalid_argument("Error with accept");
    }
    std::cout << "Connection accepted\n";
    if ((childpid = fork()) == 0) {
      close(server_socket);

      while (1) {
        memset(buffer, 0, BUF_SIZE);
        ret_bind = recv(newserver_socket, buffer, BUF_SIZE, 0);
        if (ret_bind < 0) {
          throw std::invalid_argument(
              "Error with "
              "recv"
              "");
        }
        ret_bind = send(newserver_socket, buffer, BUF_SIZE, 0);
        if (ret_bind < 0) {
          throw std::invalid_argument(
              "Error with "
              "send"
              "");
        }
        std::cout << "Received: " << buffer << "\n";
      }
    }
    close(newserver_socket);
  }
}
