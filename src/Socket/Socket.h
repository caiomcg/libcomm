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
protected:
    Uri uri_;

    int domain_;
    int is_bound_;
    int file_descriptor_;
    
    struct sockaddr_in sockaddr_info_;
public:
    Socket(const int& descriptor);
    Socket(struct sockaddr_in address, int socket_type);
    Socket(const Uri uri, int domain = AF_INET) noexcept(false);
    virtual ~Socket();

    // Socket(Socket& rhs);
    // Socket& operator=(Socket& rhs);

    // Socket(Socket&& rhs);
    // Socket& operator=(Socket&& rhs);
    void bind() noexcept(false);
    Uri getUri() const;
    struct sockaddr_in getSocketInfo() const;

    virtual void close() noexcept(false) = 0;
};