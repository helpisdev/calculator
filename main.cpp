#include "Calculator.hpp"

int main()
{
    const auto calculator = std::make_unique<Calculator>();
    calculator->run();

    return 0;
}
