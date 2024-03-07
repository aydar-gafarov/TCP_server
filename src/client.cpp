#include "client.h"

void Client::connect_client(int argc, char **argv) {
  if (argc < 3) {
    throw std::invalid_argument("Need name, port, timeout");
  }
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) {
    throw std::invalid_argument("Error with socket");
  }
  std::cout << "Socket created\n";
  client_address.sin_family = AF_INET;
  client_address.sin_addr.s_addr = htons(INADDR_ANY);
  client_address.sin_port = htons(atoi(argv[2]));

  timeout = atoi(argv[3]);
  name = argv[1];
  ret_connect = connect(client_socket, (struct sockaddr *)&client_address,
                        sizeof(client_address));
  if (ret_connect < 0) {
    throw std::invalid_argument("Error with connect");
  }
  std::cout << "Connect done\n";
}
void Client::start() {
  char buffer[BUF_SIZE];
  memset(buffer, 0, BUF_SIZE);

  std::ofstream out("log.txt", std::ios::app);
  struct tm *timeinfo;
  auto future1 = std::async(std::launch::async, [&] {
    while (1) {
      std::time_t time_cnt = time(0);
      char buffer[80];
      timeinfo = localtime(&time_cnt);
      strftime(buffer, 80, "%Y %x %X", timeinfo);
      out << "[" << buffer << "] " << name << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000) * timeout);
    }
  });

  while (1) {
    fgets(buffer, BUF_SIZE, stdin);
    out << name << ": " << buffer << std::endl;
    ret_connect = send(client_socket, buffer, BUF_SIZE, 0);
    if (ret_connect < 0) {
      std::cout << "Error with "
                   "send"
                   "\n";
    }
    ret_connect = recv(client_socket, buffer, BUF_SIZE, 0);
    if (ret_connect < 0) {
      std::cout << "Error with "
                   "recv"
                   "\n";
    } else {
      std::cout << "Received: ";
      if (buffer[0] == '.') exit(1);
      std::cout << buffer << std::endl;
    }
  }
  close(client_socket);
}
