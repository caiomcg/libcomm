#include "Socket.h"

Socket::Socket(const Uri uri) : uri_{uri}, file_descriptor_{0} {}
Socket::~Socket() {}