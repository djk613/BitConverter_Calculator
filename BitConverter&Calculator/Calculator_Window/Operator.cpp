#include "Operator.h"

Operator::Operator(char ch, bool b_negative)
{
	m_bRightValueNegative = b_negative;

	if (ch == '+')
	{
		m_nPriority = 1;
		operator_action = DigitOperator::Add;
	}
	else if (ch == '-') 
	{
		m_nPriority = 1;
		operator_action = DigitOperator::Sub;
	}
	else if (ch == '*')
	{
		m_nPriority = 2;
		operator_action = DigitOperator::Mul;
	}
	else if (ch == '/')
	{
		m_nPriority = 2;
		operator_action = DigitOperator::Div;
	}
}

void Operator::View()
{
}

