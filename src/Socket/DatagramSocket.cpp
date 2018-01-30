#include "DatagramSocket.h"

DatagramSocket::DatagramSocket(struct sockaddr_in client_address) : Socket(client_address, SOCK_DGRAM){};
DatagramSocket::DatagramSocket(const Uri uri, int domain) noexcept(false) : Socket(uri, domain) {}
DatagramSocket::~DatagramSocket() {
    this->close();
}

DatagramSocket::DatagramSocket(DatagramSocket&& rhs) : Socket(std::forward<Socket>(rhs)) {}

std::ostream& operator<<(std::ostream& stream, const DatagramSocket& datagram_socket) {
    stream << datagram_socket.uri_;
    return stream;
}

void DatagramSocket::send(const DatagramSocket& socket, std::unique_ptr<uint8_t> data, const std::size_t& size) {
    auto address = socket.getSocketInfo();
    if (sendto(this->file_descriptor_, data.get(), size, 0, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw std::runtime_error("Coulf not send Datagram data");
    }
}

void DatagramSocket::send(const DatagramSocket& socket, std::shared_ptr<uint8_t> data, const std::size_t& size) {
    auto address = socket.getSocketInfo();
    if (sendto(this->file_descriptor_, data.get(), size, 0, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw std::runtime_error("Coulf not send Datagram data " + std::string(strerror(errno)));
    }
}


DatagramPacket DatagramSocket::receive(const std::size_t& buffer_size) {
    if (!this->is_bound_) {
        throw std::runtime_error("Cannot receive on unbound socket");
    }
    struct sockaddr_in client_address;
    socklen_t size = sizeof(struct sockaddr_in);

    auto buffer = std::make_shared<uint8_t>(buffer_size);
    auto received = recvfrom(this->file_descriptor_, buffer.get(), buffer_size, 0, (struct sockaddr *) &client_address, &size);
    return DatagramPacket(std::move(buffer), received, DatagramSocket(client_address));
}

DatagramPacket DatagramSocket::receive(std::shared_ptr<uint8_t> buffer, const std::size_t& buffer_size) {
    if (!this->is_bound_) {
        throw std::runtime_error("Cannot receive on unbound socket");
    }
    struct sockaddr_in client_address;
    socklen_t size = sizeof(struct sockaddr_in);

    auto received = recvfrom(this->file_descriptor_, buffer.get(), buffer_size, 0, (struct sockaddr *) &client_address, &size);
    return DatagramPacket(std::move(buffer), received, DatagramSocket(client_address));
}

void DatagramSocket::close() {}


DatagramPacket::DatagramPacket(std::shared_ptr<uint8_t> data, std::size_t size, DatagramSocket datagram_socket) : client_address_(std::move(datagram_socket)) {
    this->data_ = std::move(data);
    this->size_ = size;
}

DatagramSocket& DatagramPacket::getClient() {
    return client_address_;
}

std::shared_ptr<uint8_t> DatagramPacket::getData() {
    return std::move(this->data_);
}

std::size_t DatagramPacket::getSize() const {
    return this->size_;
}