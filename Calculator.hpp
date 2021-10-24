//
// Created by ilias on 22/10/21.
//

#ifndef CALCULATOR_CALCULATOR_HPP
#define CALCULATOR_CALCULATOR_HPP

#include "Token.hpp"
#include <memory>
#include <queue>

class Calculator
{
private:
    double primary();
    double term();
    double expression();

public:
    Calculator();
    void run();
};

#endif //CALCULATOR_CALCULATOR_HPP
