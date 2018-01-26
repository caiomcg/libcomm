#include <iostream>

#include "Uri.h"

auto main() -> int {
    Uri uri{"udp://192.168.0.100:8080"};

    std::clog << "Connecting to: " << uri << std::endl;

    return 0;
}