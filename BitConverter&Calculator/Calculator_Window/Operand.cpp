#include "Operand.h"

Operand::Operand(string number)
{
	char sign = number.at(0);

	if (sign == 'b' || sign == 'B')
	{
		number.erase(0, 1);
		value = new Binary(number);
	}
	else if (sign == 'x' || sign == 'X')
	{
		number.erase(0, 1);
		value = new HexaDecimal(number);
	}
	else
	{
		value = new Decimal(number);
	}

	priority = 3;
}

void Operand::View()
{
}
