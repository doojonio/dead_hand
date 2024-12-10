#include "crypto.h"
#include <iostream>
#include <memory>

namespace util {

    std::string XorCryptator::encrypt(const std::string& str) {
        std::string encrypted;
        for (char c : str) {
            encrypted += c ^ k;
        }
        return encrypted;
    }

    std::string XorCryptator::decrypt(const std::string& str) {
        return encrypt(str);
    }

    std::string CryptoLine::encrypt(const std::string& str) {
        std::string result = str;
        for (const auto& c : cryptators) {
            result = c->encrypt(result);
        }
        return result;
    }

    std::string CryptoLine::decrypt(const std::string& str) {
        std::string result = str;
        for (auto c = cryptators.rbegin(); c != cryptators.rend(); c++) {
            result = (*c)->decrypt(result);
        }
        return result;
    }
} // namespace util

