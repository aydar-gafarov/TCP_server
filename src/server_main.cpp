#include "server.h"

int main(int argc, char **argv) {
  Server serv;
  serv.bind_server(argc, argv);
  serv.start();
}
