//
// Created by ilias on 23/10/21.
//

#ifndef CALCULATOR_TOKENSTREAM_HPP
#define CALCULATOR_TOKENSTREAM_HPP

#include "Token.hpp"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

class TokenStream
{
private:
    const std::unique_ptr<std::queue<Token>> tokens_{ std::make_unique<std::queue<Token>>() };
    std::string input_;
    bool is_buffer_full_{ false };
    std::unique_ptr<Token> buffer_{ nullptr };
    bool should_exit_program_{ false };

    void getInput();
    void tokenizeInput() const;

public:
    TokenStream();
    void pollForInput();
    [[nodiscard]] Token getToken();
    void putback(std::unique_ptr<Token> token);
    [[nodiscard]] bool getExitStatus() const;
    [[nodiscard]] bool getCalculationStatus() const;
};

template <typename T>
void g_clear_queue(std::queue<T>& queue)
{
    queue = {};
}

#endif //CALCULATOR_TOKENSTREAM_HPP
