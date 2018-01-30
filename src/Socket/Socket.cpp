#include "Socket.h"

Socket::Socket(const int& descriptor) {
    this->file_descriptor_ = descriptor;
}

Socket::Socket(struct sockaddr_in address, int socket_type) {
    this->sockaddr_info_ = address;

    if ((file_descriptor_ = socket(address.sin_family, socket_type, 0)) == -1) {
        throw std::runtime_error("Could not create the socket - " + std::string(strerror(errno)));
    }

    auto ip = inet_ntoa(this->sockaddr_info_.sin_addr);
    uint16_t port = ntohs(this->sockaddr_info_.sin_port);

    uri_ = Uri("udp://" + std::string(ip) + ":" + std::to_string(port));
}

Socket::Socket(const Uri uri, int domain) : uri_{uri}, domain_{domain}, is_bound_{false}, file_descriptor_{-1} {   
    int type = 0;
    
    memset((char*)&this->sockaddr_info_, 0, sizeof(this->sockaddr_info_));
    this->sockaddr_info_.sin_family      = this->domain_;
    this->sockaddr_info_.sin_port        = htons(this->uri_.getPort());
    this->sockaddr_info_.sin_addr.s_addr = (this->uri_.getHost() == "@" ? INADDR_ANY : inet_addr(this->uri_.getHost().c_str()));

    if (this->uri_.getScheme() == "udp") {
        type = SOCK_DGRAM;
    } else if (this->uri_.getScheme() == "tcp" || this->uri_.getScheme() == "http") {
        type = SOCK_STREAM;
    } else {
        throw std::runtime_error("Unknown Uri scheme - " + this->uri_.getScheme());
    }

    if ((file_descriptor_ = socket(this->domain_, type, 0)) == -1) {
        throw std::runtime_error("Could not create the socket - " + std::string(strerror(errno)));
    }
}

Socket::~Socket() {}

void Socket::setOpt(int level, int opt_name) {
    int flag = 1;

    if (setsockopt(this->file_descriptor_, level, opt_name, &flag, sizeof(int)) == -1) {
        throw std::runtime_error("Could not setsockopt: " + std::string(strerror(errno)));
    }
}

void Socket::setFlags(int flags) {
    if (flags & FLAG::REUSE_ADDR) {
        this->setOpt(SOL_SOCKET, SO_REUSEADDR);
    }
    
    if (flags & FLAG::BROADCAST) {
        this->setOpt(SOL_SOCKET, SO_BROADCAST);
    }

    if (flags & FLAG::MULTICAST_IF) {
        this->setOpt(IPPROTO_IP, IP_MULTICAST_IF);
    }

    if (flags & FLAG::MULTICAST_LOOP) {
        this->setOpt(IPPROTO_IP, IP_MULTICAST_LOOP);
    }
}

void Socket::bind() {
    if (::bind(this->file_descriptor_, (struct sockaddr*)&this->sockaddr_info_, sizeof(this->sockaddr_info_)) == -1) {
		throw std::runtime_error("Could not bind the socket: " + std::string(strerror(errno)));
	}

    this->is_bound_ = true;
}

Uri Socket::getUri() const {
    return this->uri_;
}

struct sockaddr_in Socket::getSocketInfo() const {
    return this->sockaddr_info_;
}