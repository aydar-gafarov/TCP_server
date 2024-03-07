#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include <ctime>
#include <fstream>
#include <future>
#include <iostream>
#define BUF_SIZE 2000

class Client {
 public:
  int port = 0;
  int ret_connect = 0;
  int timeout = 0;
  char *name;
  sockaddr_in client_address = {0};
  int client_socket = 0;
  void connect_client(int argc, char **argv);
  void start();
};

#endif  // CLIENT_H