#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include "chat_server.hpp"

int main(int argc, char* argv[]) {
  try {
    if (argc < 2) {
      std::cerr << "Usage: chat_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
    chat_server server(io_context, endpoint);
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}