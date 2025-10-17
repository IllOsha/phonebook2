#pragma once
#include <string>
#include <regex>

namespace Validators {

inline std::string trim(const std::string &s) {
    size_t b = 0;
    while (b < s.size() && isspace((unsigned char)s[b])) ++b;
    size_t e = s.size();
    while (e > b && isspace((unsigned char)s[e - 1])) --e;
    return s.substr(b, e - b);
}

inline bool validname(const std::string &s) {
    auto t = trim(s);
    if (t.empty()) return false;
    static const std::regex re("^[A-Za-zА-Яа-яЁё][A-Za-zА-Яа-яЁё\\- ]*$");
    return std::regex_match(t, re);
}

inline bool validphone(const std::string &s) {
    std::string t;
    for (char d : s) {
        if (isdigit((unsigned char)d) || d == '+' || d == '8')
            t.push_back(d);
    }
    static const std::regex re(R"(^(?:\+7|8)\d{10}$)");
    return std::regex_match(t, re);
}

inline bool valiemail(const std::string &s) {
    auto t = trim(s);
    static const std::regex re(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(t, re);
}

}  
