#pragma once

#include "Socket.h"

class DatagramPacket; // Forward declaration

class DatagramSocket final : public Socket {
public:
    DatagramSocket(struct sockaddr_in client_address);
    DatagramSocket(const Uri uri, int domain = AF_INET) noexcept(false);
    ~DatagramSocket() override;

    DatagramSocket(const DatagramSocket& rhs);
    DatagramSocket& operator=(const DatagramSocket& rhs);

    DatagramSocket(DatagramSocket&& rhs);

    friend std::ostream& operator<<(std::ostream& stream, const DatagramSocket& datagram_socket);

    void send(const DatagramSocket& socket, std::shared_ptr<uint8_t> data, const std::size_t& size) noexcept(false);

    DatagramPacket receive(const std::size_t& buffer_size) noexcept(false);
    DatagramPacket receive(std::shared_ptr<uint8_t> buffer, const std::size_t& buffer_size) noexcept(false);

    void close() override;
};

class DatagramPacket {
private:
    DatagramSocket client_address_;
    std::shared_ptr<uint8_t> data_;
    std::size_t size_;
public:
    DatagramPacket(std::shared_ptr<uint8_t> data, std::size_t size, DatagramSocket datagram_socket);

    DatagramSocket getClient();
    std::shared_ptr<uint8_t> getData();
    std::size_t getSize() const;
};