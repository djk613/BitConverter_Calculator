#include "Operator.h"

Operator::Operator(char ch, bool b_negative)
{
	m_bRightValueNegative = b_negative;

	if (ch == '+')
	{
		priority = 1;
		operator_action = DigitOperator::Add;
	}
	else if (ch == '-') 
	{
		priority = 1;
		operator_action = DigitOperator::Sub;
	}
	else if (ch == '*')
	{
		priority = 2;
		operator_action = DigitOperator::Mul;
	}
	else if (ch == '/')
	{
		priority = 2;
		operator_action = DigitOperator::Div;
	}
}

void Operator::View()
{
}

