cmake_minimum_required(VERSION 3.20)
project(Calculator)

set(CMAKE_CXX_STANDARD 23)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

add_executable(Calculator main.cpp Calculator.cpp Calculator.hpp Token.cpp Token.hpp TokenType.hpp TokenStream.cpp TokenStream.hpp InputSpecialValue.hpp Operator.hpp CalculationError.cpp CalculationError.hpp)
