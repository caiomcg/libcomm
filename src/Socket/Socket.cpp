#include "Socket.h"

Socket::Socket(const Uri uri, int domain) : uri_{uri}, file_descriptor_{0} {   
    int type = 0;
 
    if (this->uri_.getScheme() == "udp") {
        type = SOCK_DGRAM;
    } else if (this->uri_.getScheme() == "tcp" || this->uri_.getScheme() == "http") {
        type = SOCK_STREAM;
    } else {
        throw std::runtime_error("Unknown Uri scheme - " + this->uri_.getScheme());
    }

    if ((file_descriptor_ = socket(domain, type, 0)) == -1) {
        throw std::runtime_error("Could not create the socket - " + std::string(strerror(file_descriptor_)));
    }

    static_assert(sizeof(char) == 1, "A char should be one byte long");

    memset((char*)&this->sockaddr_info_, 0, sizeof(this->sockaddr_info_));
    this->sockaddr_info_.sin_family      = domain;
    this->sockaddr_info_.sin_port        = htons(this->uri_.getPort());
    this->sockaddr_info_.sin_addr.s_addr = (this->uri_.getHost() == "@" ? INADDR_ANY : inet_addr(this->uri_.getHost().c_str()));

}

Socket::~Socket() {}

Uri Socket::getUri() const {
    return this->uri_;
}