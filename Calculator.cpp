//
// Created by ilias on 22/10/21.
//

#include "Calculator.hpp"
#include "CalculationError.hpp"
#include <cmath>
#include <iostream>

Calculator::Calculator() = default;

double Calculator::primary()
{
    double left_operand;
    switch (Token token{ this->token_stream_.getToken() }; token.getType()) {
    case TokenType::OPERATOR:
        if (Operator{ static_cast<Operator>(token.getValue()) } == Operator::LEFT_PARENTHESIS) {
            const double expression_result = this->expression();
            token = this->token_stream_.getToken();
            if (Operator{ static_cast<Operator>(token.getValue()) } != Operator::RIGHT_PARENTHESIS) {
                throw std::invalid_argument("Right parenthesis expected");
            }
            return expression_result;
        }
        throw CalculationError("Unexpected Primary");
    case TokenType::NUMBER:
        left_operand = token.getValue();
        token = this->token_stream_.getToken();
        if (Operator{ static_cast<Operator>(token.getValue()) } == Operator::POWER) {
            token = this->token_stream_.getToken();
            double right_operand = token.getValue();
            return std::pow(left_operand, right_operand);
        }
        this->token_stream_.putback(std::make_unique<Token>(token));
        return left_operand;
    default:
        throw CalculationError("Unexpected token");
    }
}

double Calculator::term()
{
    double left_operand = this->primary();
    Token token = this->token_stream_.getToken();
    bool is_term{ true };

    while (is_term) {
        double divisor;
        switch (Operator{ static_cast<Operator>(token.getValue()) }) {
        case Operator::MULTIPLICATION:
            left_operand *= this->primary();
            break;
        case Operator::DIVISION:
            divisor = this->primary();
            if (divisor == 0.0) {
                throw std::overflow_error("Divide by zero exception");
            }
            left_operand /= divisor; //throw division exception
            break;
        default:
            this->token_stream_.putback(std::make_unique<Token>(token));
            is_term = false;
            break;
        }

        if (is_term) {
            token = this->token_stream_.getToken();
        }
    }

    return left_operand;
}

double Calculator::expression()
{
    double left_operand = this->term();
    Token token = this->token_stream_.getToken();
    bool is_expression{ true };

    while (is_expression) {
        switch (Operator{ static_cast<Operator>(token.getValue()) }) {
        case Operator::ADDITION:
            left_operand += this->term();
            break;
        case Operator::SUBTRACTION:
            left_operand -= this->term();
            break;
        default:
            this->token_stream_.putback(std::make_unique<Token>(token));
            is_expression = false;
            break;
        }

        if (is_expression) {
            token = this->token_stream_.getToken();
        }
    }

    return left_operand;
}

void Calculator::calculate()
{
    try {
        std::cout << "= " << this->expression() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Calculator::run()
{
    bool should_exit{ false };
    do {
        try {
            this->token_stream_.pollForInput();

            if (this->token_stream_.getCalculationStatus()) {
                this->calculate();
            }
            should_exit = this->token_stream_.getExitStatus();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    } while (!should_exit);
}
