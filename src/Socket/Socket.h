#pragma once

#include "Uri.h"

// Networking Headers
//---------------------------------------------------------------------------------------------
#include <arpa/inet.h>   		 // Networking.
#include <netinet/in.h>  		 // Networking.
#include <sys/types.h>   		 // Networking.
#include <sys/socket.h>  		 // Networking.
#include <sys/stat.h>    		 // Networking.
#include <unistd.h>   	 		 // Unix default header.
//---------------------------------------------------------------------------------------------

class Socket {
protected:
    Uri uri_;
    int file_descriptor_;
public:
    Socket(const Uri uri);
    virtual ~Socket();

    // Socket(Socket& rhs);
    // Socket& operator=(Socket& rhs);

    // Socket(Socket&& rhs);
    // Socket& operator=(Socket&& rhs);

    virtual void bind() noexcept(false) = 0;
    virtual void close() noexcept(false) = 0;
};