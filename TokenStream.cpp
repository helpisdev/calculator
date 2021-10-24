//
// Created by ilias on 23/10/21.
//

#include "TokenStream.hpp"
#include "InputSpecialValue.hpp"
#include <iostream>

TokenStream::TokenStream() = default;

void TokenStream::pollForInput(std::mutex& mutex, std::condition_variable& poll, const bool& should_poll)
{
    do {
        std::unique_lock lock(mutex);
        g_clear_queue(*this->tokens_);
        this->getInput();
        this->tokenizeInput();
        poll.wait(lock, [&should_poll]() {
            return should_poll;
        });
    } while (!this->should_exit_program_);
}

void TokenStream::getInput()
{
    std::string stringified_input;
    char input_character;
    bool should_calculate{ false };

    do {
        bool should_ignore_next_char{ false };
        const int next_char = std::cin.peek();
        if (next_char == static_cast<const int>(InputSpecialValue::SPACE)) {
            should_ignore_next_char = true;
        }

        if (next_char == static_cast<const int>(InputSpecialValue::ENTER_PROMT) ||
            next_char == static_cast<const int>(InputSpecialValue::EQUALS_PROMT)) {
            should_calculate = true;
            should_ignore_next_char = true;
        }

        if (next_char == static_cast<const int>(InputSpecialValue::EXIT) ||
            next_char == std::char_traits<char>::eof()) {
            this->should_exit_program_ = true;
            should_ignore_next_char = true;
        }

        if (should_ignore_next_char) {
            static_cast<void>(std::cin.ignore());
        }
        else {
            std::cin >> input_character;
            stringified_input.push_back(input_character);
        }

    } while (!should_calculate && !this->should_exit_program_);

    this->input_ = stringified_input;
}

void TokenStream::tokenizeInput() const
{
    std::string token;
    for (char character : this->input_) {
        if ((character >= '0' && character <= '9') || character == '.') {
            token += character;
        }
        else {
            if (!token.empty()) {
                this->tokens_->push(Token(token));
            }
            token = character;
            this->tokens_->push(Token(token));
            token.clear();
        }
    }
}

const Token& TokenStream::getToken()
{
    if (this->is_buffer_full_) {
        this->is_buffer_full_ = false;
        const Token& token_buffer = *this->buffer_;
        this->buffer_ = nullptr;
        return token_buffer;
    }
    return this->tokens_->front();
}

void TokenStream::putback(const Token* token)
{
    this->buffer_ = token;
    this->is_buffer_full_ = true;
}
