//
// Created by ilias on 24/10/21.
//

#ifndef CALCULATOR_CALCULATIONERROR_HPP
#define CALCULATOR_CALCULATIONERROR_HPP

#include <stdexcept>

class CalculationError : public std::runtime_error
{
private:
    const std::string error_message_;

public:
    explicit CalculationError(const std::string& error_message);
};

#endif //CALCULATOR_CALCULATIONERROR_HPP
