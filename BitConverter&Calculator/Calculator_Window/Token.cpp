#include "Token.h"

bool Token::MoreThanPriority(Token* token)
{
    return m_nPriority >= token->m_nPriority;
}
