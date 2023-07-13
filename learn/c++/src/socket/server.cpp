#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
  // 创建套接字
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    return 1;
  }

  // 绑定套接字到地址和端口
  sockaddr_in server_addr;
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(8080);

  if (bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to bind socket" << std::endl;
    return 1;
  }

  // 监听套接字
  if (listen(server_socket, 1) == -1) {
    std::cerr << "Failed to listen on socket" << std::endl;
    return 1;
  }

  // 接受客户端连接
  sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int client_socket = accept(server_socket, (sockaddr *)&client_addr, &client_addr_len);
  if (client_socket == -1) {
    std::cerr << "Failed to accept client connection" << std::endl;
    return 1;
  }

  // 接收并返回客户端消息
  char buffer[256];
  ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
  if (bytes_received == -1) {
    std::cerr << "Failed to receive message from client" << std::endl;
    return 1;
  }

  buffer[bytes_received] = '\0';
  std::cout << "Received message: " << buffer << std::endl;

  if (send(client_socket, buffer, bytes_received, 0) == -1) {
    std::cerr << "Failed to send message back to client" << std::endl;
    return 1;
  }

  // 关闭套接字
  close(client_socket);
  close(server_socket);

  return 0;
}