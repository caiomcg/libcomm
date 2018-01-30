#include <iostream>

#include "DatagramSocket.h"

auto main() -> int {
    DatagramSocket datagram_socket{Uri{"udp://@:8080"}};
    datagram_socket.setFlags(DatagramSocket::FLAG::REUSE_ADDR);
    datagram_socket.bind();

    auto buffer = std::make_shared<uint8_t>(1024);
    buffer.get()[0] = 'T';
    buffer.get()[1] = 'E';
    buffer.get()[2] = 'S';
    buffer.get()[3] = 'T';
    buffer.get()[4] = '\0';

    std::clog << "Listening at: " << datagram_socket << std::endl;

    auto packet = datagram_socket.receive(1024);

    std::clog << "Message: " << packet.getData().get() << " - Size: " << packet.getSize() << std::endl;
    std::clog << "Sending to: " << packet.getClient() << " - message: " << buffer.get() << std::endl;

    datagram_socket.send(packet.getClient(), buffer, 5);
    return 0;
}