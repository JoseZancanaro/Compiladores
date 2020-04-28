#include "Lexical.hpp"

namespace wpl {

auto Lexical::set_input(const char *input) -> void {
    this->input = input;
    set_position(0);
}

auto Lexical::next_token() -> Token* {
    if ( ! has_input() )
        return 0;

    unsigned start = position;

    int state = 0;
    int oldState = 0;
    int endState = -1;
    int end = -1;

    while (has_input())
    {
        oldState = state;
        state = next_state(next_char(), state);

        if (state < 0)
            break;

        else
        {
            if (token_for_state(state) >= 0)
            {
                endState = state;
                end = position;
            }
        }
    }
    if (endState < 0 /*|| (endState != state && token_for_state(oldState) == -2)*/)
        throw Lexical_Error(SCANNER_ERROR[oldState], start);

    position = end;

    Token_Id token = token_for_state(endState);

    if (token == 0)
        return next_token();
    else
    {
        std::string lexeme = input.substr(start, end-start);
        token = lookup_token(token, lexeme);
        return new Token(token, lexeme, start);
    }
}

int Lexical::next_state(unsigned char c, int state) const
{
    int next = SCANNER_TABLE[state][c];
    return next;
}

Token_Id Lexical::token_for_state(int state) const
{
    int token = -1;

    if (state >= 0 && state < STATES_COUNT)
        token = TOKEN_STATE[state];

    return static_cast<Token_Id>(token);
}

Token_Id Lexical::lookup_token(Token_Id base, const std::string &key)
{
    int start = SPECIAL_CASES_INDEXES[base];
    int end   = SPECIAL_CASES_INDEXES[base+1]-1;

    while (start <= end)
    {
        int half = (start+end)/2;
        const std::string current = SPECIAL_CASES_KEYS[half];

        if (current == key)
            return static_cast<Token_Id>(SPECIAL_CASES_VALUES[half]);
        else if (current < key)
            start = half+1;
        else
            end = half-1;
    }

    return base;
}

} //namespace wpl

