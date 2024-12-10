#pragma once
#include <vector>
#include <string>
#include <memory>

#include <iostream>

namespace util {
    struct BaseCryptator {
        [[nodiscard]] virtual std::string encrypt(const std::string& str) = 0;
        [[nodiscard]] virtual std::string decrypt(const std::string& str) = 0;

        virtual ~BaseCryptator() = default;
    };


    class XorCryptator : public BaseCryptator {
        char k;

    public:
        XorCryptator(char k) : k(k) {};
        [[nodiscard]] std::string encrypt(const std::string& str) override;
        [[nodiscard]] std::string decrypt(const std::string& str) override;
    };

    class CryptoLine {
        std::vector<std::unique_ptr<BaseCryptator>> cryptators;

    public:
        CryptoLine() {
            cryptators.push_back(std::make_unique<XorCryptator>('a'));
            cryptators.push_back(std::make_unique<XorCryptator>('b'));
            cryptators.push_back(std::make_unique<XorCryptator>('c'));
            cryptators.push_back(std::make_unique<XorCryptator>('d'));
            cryptators.push_back(std::make_unique<XorCryptator>('e'));
            cryptators.push_back(std::make_unique<XorCryptator>('f'));
            cryptators.push_back(std::make_unique<XorCryptator>('g'));
        }

        [[nodiscard]] std::string encrypt(const std::string& str);
        [[nodiscard]] std::string decrypt(const std::string& str);
    };

    template<typename T>
    class Crypted {
        CryptoLine cline;
        std::string value;
    public:
        inline Crypted(T&& v) : value(cline.encrypt(v.ser())) { std::cout << value << std::endl; }
        [[nodiscard]] inline T decrypt() { return T::de(cline.decrypt(value)); };
    };


} // namespace encr

