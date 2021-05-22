#include "Token.h"

bool Token::MoreThanPriority(Token* token)
{
    return priority >= token->priority;
}
