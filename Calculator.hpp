//
// Created by ilias on 22/10/21.
//

#ifndef CALCULATOR_CALCULATOR_HPP
#define CALCULATOR_CALCULATOR_HPP

#include "Token.hpp"
#include "TokenStream.hpp"
#include <condition_variable>
#include <memory>
#include <mutex>

class Calculator
{
private:
    TokenStream token_stream_{ TokenStream() };

    [[nodiscard]] double primary();
    [[nodiscard]] double term();
    [[nodiscard]] double expression();
    void calculate();

public:
    Calculator();
    void run();
};

#endif //CALCULATOR_CALCULATOR_HPP
