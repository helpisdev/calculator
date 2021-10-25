//
// Created by ilias on 22/10/21.
//

#ifndef CALCULATOR_TOKEN_HPP
#define CALCULATOR_TOKEN_HPP

#include "TokenType.hpp"
#include <string>
#include "Operator.hpp"

class Token
{
private:
    TokenType type_{};
    double value_{};

public:
    explicit Token(const std::string& input);
    [[nodiscard]] const TokenType& getType() const;
    [[nodiscard]] double getValue() const;

//    Token& operator=(Token other_token) noexcept; // copy assignment - copy and swap
    Token& operator=(const Token& other_token) noexcept; // copy assignment
//    Token& operator=(Token&& other_token) noexcept; // move assignment
//    Token(const Token& other_token); // copy constructor
//    Token(Token&& other_token) noexcept; // move constructor
    ~Token() = default; // destructor
    Token() = default;
};

#endif //CALCULATOR_TOKEN_HPP
