#include <iostream>

#include "Uri.h"

auto main() -> int {
    Uri uri{"udp://192.168.0.100:8080"};

    std::clog << uri.getHost() << std::endl;
    std::clog << uri.getPort() << std::endl;
    std::clog << uri.getScheme() << std::endl;

    return 0;
}