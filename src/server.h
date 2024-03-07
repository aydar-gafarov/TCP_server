#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#define BUF_SIZE 2000

class Server {
 public:
  Server() {}
  sockaddr_in server_address = {0};
  int server_socket = 0;
  int port = 0;
  int ret_bind = 0;
  void bind_server(int argc, char** argv);
  void start();
};

#endif  // SERVER_H
