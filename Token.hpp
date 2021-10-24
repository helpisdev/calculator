//
// Created by ilias on 22/10/21.
//

#ifndef CALCULATOR_TOKEN_HPP
#define CALCULATOR_TOKEN_HPP

#include "TokenType.hpp"
#include <string>

class Token
{
private:
    TokenType type_;
    double value_;

    enum class Operator : char
    {
        ADDITION = '+',
        SUBTRACTION = '-',
        MULTIPLICATION = '*',
        DIVISION = '/',
        POWER = '^',
        LEFT_PARENTHESIS = '(',
        RIGHT_PARENTHESIS = ')'
    };

public:
    explicit Token(const std::string& input);
    [[nodiscard]] const TokenType& getType() const;
    [[nodiscard]] double getValue() const;
};

#endif //CALCULATOR_TOKEN_HPP
