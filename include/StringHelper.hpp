#pragma once

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

static inline std::string toLower(const std::string &str) {
    std::stringstream newStr;
    const auto highToLow = 'A' - 'a';
    for(const char &c : str) {
        if(c >= 'A' && c <= 'Z') {
            newStr << static_cast<char>(c - highToLow);
        } else {
            newStr << c;
        }
    }
    return newStr.str();
}

static inline std::string remove(
        const std::string &str, const char &toRemove) {
    std::stringstream newStr;
    for(const char &c : str) {
        if(c != toRemove) {
            newStr << c;
        }
    }
    return newStr.str();
}

static inline std::string trim(const std::string &str) {
    auto strMutCopy = str;
    strMutCopy.erase(
        strMutCopy.begin(), std::find_if(
            strMutCopy.begin(), strMutCopy.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }
        )
    );
    strMutCopy.erase(
        std::find_if(
            strMutCopy.rbegin(), strMutCopy.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }
        ).base(), strMutCopy.end()
    );
    return strMutCopy;
}

static inline bool endsWith(
        const std::string &mainStr, const std::string &toMatch) {
    if(mainStr.size() >= toMatch.size() &&
            mainStr.compare(
                mainStr.size() - toMatch.size(), toMatch.size(), toMatch
            ) == 0) {
        return true;
    } else {
        return false;
    }
}

static inline std::vector<std::string> split(
        const std::string &str, const std::string &splitStr) {
    std::vector<std::string> subStrs;

    // Loop through all space-separated strings
    auto strMutCpy = str;
    if(!endsWith(strMutCpy, splitStr)) {
        strMutCpy += splitStr;
    }
    size_t pos = 0;
    while((pos = strMutCpy.find(splitStr)) != std::string::npos) {
        const auto substr = strMutCpy.substr(0, pos);
        subStrs.push_back(substr);
        strMutCpy.erase(0, pos + 1);
    }

    return subStrs;
}
