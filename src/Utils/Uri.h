#pragma once

//Should comply with RFC 2396

#include <regex>
#include <string>

class Uri final {
private: 
    std::string url_;
    std::string scheme_;
    std::string authority_;
public:
    Uri(const std::string& url);
    ~Uri();

    std::string getScheme() const;
    std::string getHost() const;
    int getPort() const;
};