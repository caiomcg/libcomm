#include "Uri.h"

Uri::Uri(const std::string& url) : url_{url} {
    scheme_    = this->url_.substr(0, this->url_.find_first_of(':'));
    authority_ = this->url_.substr(this->url_.find_first_of(':') + 1);
}

Uri::~Uri() {}

std::ostream& operator<<(std::ostream& stream, const Uri& uri) {
    stream << uri.url_;
    return stream;
}

std::string Uri::getScheme() const {
    return this->scheme_;
}

std::string Uri::getHost() const {
    return this->authority_.substr(2, this->authority_.find_first_of(':') - 2);
}

int Uri::getPort() const {
    return std::stoi(this->authority_.substr(this->authority_.find_first_of(':') + 1));
}