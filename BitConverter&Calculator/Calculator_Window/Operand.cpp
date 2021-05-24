#include "Operand.h"

Operand::Operand(string str_number)
{
	char ch_sign = str_number.at(0);

	if (ch_sign == 'b' || ch_sign == 'B')
	{
		str_number.erase(0, 1);
		value = new Binary(str_number);
	}
	else if (ch_sign == 'x' || ch_sign == 'X')
	{
		str_number.erase(0, 1);
		value = new HexaDecimal(str_number);
	}
	else
	{
		value = new Decimal(str_number);
	}

	m_nPriority = 3;
}

void Operand::View()
{
}
