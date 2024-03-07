#include "client.h"

int main(int argc, char **argv) {
  Client cl;
  cl.connect_client(argc, argv);
  cl.start();
}
