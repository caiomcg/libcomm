#pragma once

#include <assert.h>
#include <string.h>
#include <unistd.h>   	 		 // Unix default header.

#include "Uri.h"

// Networking Headers
//---------------------------------------------------------------------------------------------
#include <arpa/inet.h>   		 // Networking.
#include <netinet/in.h>  		 // Networking.
#include <sys/types.h>   		 // Networking.
#include <sys/socket.h>  		 // Networking.
#include <sys/stat.h>    		 // Networking.
//---------------------------------------------------------------------------------------------

#include <iostream>

class Socket {
private:
    void setOpt(int level, int opt_name) noexcept(false);
protected:
    Uri uri_;

    int domain_;
    int is_bound_;
    int file_descriptor_;
    
    struct sockaddr_in sockaddr_info_;
public:
    enum FLAG {
        REUSE_ADDR = 1 << 0,
        BROADCAST = 1 << 1,
        MULTICAST_IF = 1 << 2,
        MULTICAST_LOOP = 1 << 3
    };

    Socket(const int& descriptor);
    Socket(struct sockaddr_in address, int socket_type);
    Socket(const Uri uri, int domain = AF_INET) noexcept(false);
    virtual ~Socket();

    Socket(const Socket& rhs);
    Socket& operator=(const Socket& rhs);

    // Socket(Socket&& rhs);
    // Socket& operator=(Socket&& rhs);
    
    void setFlags(int flags) noexcept(false);

    void bind() noexcept(false);
    
    Uri getUri() const;
    struct sockaddr_in getSocketInfo() const;

    virtual void close() noexcept(false) = 0;
};