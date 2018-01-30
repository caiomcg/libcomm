#include <iostream>

#include "DatagramSocket.h"

auto main() -> int {
    DatagramSocket datagram_socket{Uri{"udp://127.0.0.1:8080"}};
    datagram_socket.bind();
    
    return 0;
}