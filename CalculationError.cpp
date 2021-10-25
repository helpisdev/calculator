//
// Created by ilias on 24/10/21.
//

#include "CalculationError.hpp"

CalculationError::CalculationError(const std::string& error_message)
    : runtime_error(error_message) {}
