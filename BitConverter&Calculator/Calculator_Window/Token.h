#pragma once
#include "Includes.h"

class Token
{
public:
    virtual void View() = 0;
    bool MoreThanPriority(Token* token);

public:
	int priority;
};
