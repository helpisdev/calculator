//
// Created by ilias on 23/10/21.
//

#include "TokenStream.hpp"
#include "InputSpecialValue.hpp"
#include <iostream>
#include <memory>

TokenStream::TokenStream() = default;

void TokenStream::pollForInput()
{
    this->buffer_.reset();
    this->is_buffer_full_ = false;
    g_clear_queue(*this->tokens_);
    this->getInput();
    this->tokenizeInput();
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
            if (!this->tokens_->empty()) {
                this->tokens_->push(Token(token));
                token.clear();
            }
        }
    }

    if (!token.empty()) {
        this->tokens_->push(Token(token));
        token.clear();
    }
}

Token TokenStream::getToken()
{
    if (this->is_buffer_full_) {
        this->is_buffer_full_ = false;
        Token token_buffer = *this->buffer_;
        this->buffer_.reset();
        return token_buffer;
    }
    Token token = this->tokens_->front();
    this->tokens_->pop();
    return token;
}

void TokenStream::putback(std::unique_ptr<Token> token)
{
    this->buffer_ = std::make_unique<Token>(*token);
    this->is_buffer_full_ = true;
}

bool TokenStream::getExitStatus() const
{
    return this->should_exit_program_;
}
bool TokenStream::getCalculationStatus() const
{
    return !this->tokens_->empty();
}
