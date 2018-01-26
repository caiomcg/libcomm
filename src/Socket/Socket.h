#pragma once

#include "Uri.h"

#include <assert.h>
#include <string.h>
#include <unistd.h>   	 		 // Unix default header.

// Networking Headers
//---------------------------------------------------------------------------------------------
#include <arpa/inet.h>   		 // Networking.
#include <netinet/in.h>  		 // Networking.
#include <sys/types.h>   		 // Networking.
#include <sys/socket.h>  		 // Networking.
#include <sys/stat.h>    		 // Networking.
//---------------------------------------------------------------------------------------------

class Socket {
protected:
    Uri uri_;
    int file_descriptor_;

    struct sockaddr_in sockaddr_info_;
public:
    Socket();
    Socket(const Uri uri, int domain = AF_INET) noexcept(false);
    virtual ~Socket();

    // Socket(Socket& rhs);
    // Socket& operator=(Socket& rhs);

    // Socket(Socket&& rhs);
    // Socket& operator=(Socket&& rhs);

    Uri getUri() const;

    virtual void bind() noexcept(false) = 0;
    virtual void close() noexcept(false) = 0;
};