#pragma once
#include "Token.h"
#include "DigitOperator.h"

class Operator : public Token
{
public:
	typedef string(*OperatorFunc)(string, string);

public:
	Operator(char ch, bool b_negative = false);
	
	virtual void View();

public:
	OperatorFunc operator_action;
	/*unary negative check*/
	bool m_bRightValueNegative;
};

