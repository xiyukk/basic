#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  // 创建套接字
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    return 1;
  }

  // 连接到服务器
  sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(8080);

  if (connect(client_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to connect to server" << std::endl;
    return 1;
  }

  // 向服务器发送消息
  const char *message = "Hello, server!";
  if (send(client_socket, message, std::strlen(message), 0) == -1) {
    std::cerr << "Failed to send message to server" << std::endl;
    return 1;
  }

  // 接收服务器返回的消息
  char buffer[256];
  ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
  if (bytes_received == -1) {
    std::cerr << "Failed to receive message from server" << std::endl;
    return 1;
  }

  buffer[bytes_received] = '\0';
  std::cout << "Received message: " << buffer << std::endl;

  // 关闭套接字
  close(client_socket);

  return 0;
}