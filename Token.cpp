//
// Created by ilias on 22/10/21.
//

#include "Token.hpp"
#include <stdexcept>
#include <utility>

Token::Token(const std::string& input)
{
    if (input.size() > static_cast<std::size_t>(1)) {
        this->type_ = TokenType::NUMBER;
        this->value_ = std::stod(input);

        return;
    }

    char input_mono_symbol{ input[static_cast<std::size_t>(0)] };
    switch (const Operator input_operator{ static_cast<Operator>(input_mono_symbol) }; input_operator) {
    case Operator::ADDITION:
        this->value_ = static_cast<double>(Operator::ADDITION);
        break;
    case Operator::SUBTRACTION:
        this->value_ = static_cast<double>(Operator::SUBTRACTION);
        break;
    case Operator::MULTIPLICATION:
        this->value_ = static_cast<double>(Operator::MULTIPLICATION);
        break;
    case Operator::DIVISION:
        this->value_ = static_cast<double>(Operator::DIVISION);
        break;
    case Operator::POWER:
        this->value_ = static_cast<double>(Operator::POWER);
        break;
    case Operator::LEFT_PARENTHESIS:
        this->value_ = static_cast<double>(Operator::LEFT_PARENTHESIS);
        break;
    case Operator::RIGHT_PARENTHESIS:
        this->value_ = static_cast<double>(Operator::RIGHT_PARENTHESIS);
        break;
    default:
        this->value_ = std::stod(input);
        this->type_ = TokenType::NUMBER;
        return;
    }

    this->type_ = TokenType::OPERATOR;
}

const TokenType& Token::getType() const
{
    return this->type_;
}

double Token::getValue() const
{
    return this->value_;
}

Token& Token::operator=(const Token& other_token) noexcept
{
    if (this == &other_token) {
        return *this;
    }

    this->value_ = other_token.value_;
    this->type_ = other_token.type_;

    return *this;
}
