#include "Decimal.h"

Decimal::Decimal()
{
	digitNumber = "0";
}

Decimal::Decimal(string str_num)
{
	SetNumber(str_num);
}

string Decimal::ConvertToBinary()
{
	bool b_negative = digitNumber.at(0) == '-';

	string result;
	string number = digitNumber;

	if (number == "0")
	{
		return "0";
	}

	if (b_negative)
	{
		number.erase(0, 1);
	}

	while (true)
	{
		int n_oneDigit = (number.at(number.length() - 1) & ~0b0110000);
		int nu = number.length() - 1;
		if (n_oneDigit % 2) 
		{
			result = "1" + result;
		}
		else
		{
			result = "0" + result;
		}

		if (number == "1")
		{
			break;
		}

		number = DigitOperator::Div(number, "2");
	}

	if (b_negative)
	{
		result = DigitOperator::GetTwoComplement(result);
		result = "1" + result;
	}
	else
	{
		result = "0" + result;
	}

	return result;
}

string Decimal::ConvertToDecimal()
{
	if (digitNumber[0] == '-')
	{
		digitNumber = "(" + digitNumber + ")";
	}

	return digitNumber;
}

string Decimal::ConvertToHexaDecimal()
{
	Binary bin(ConvertToBinary());

	return bin.ConvertToHexaDecimal();
}

void Decimal::SetNumber(string str_num)
{
	digitNumber = str_num;

	if (digitNumber[0] == '(' && digitNumber[digitNumber.length() - 1] == ')')
	{
		digitNumber.erase(digitNumber.length() - 1, 1);
		digitNumber.erase(0, 1);
	}

	int loopIdx = 0u;
	int number_len = digitNumber.length();
	if (digitNumber.at(0) == '-')
	{
		loopIdx++;
		number_len--;
	}

	for (; loopIdx < number_len; loopIdx++)
	{
		unsigned int num = digitNumber.at(loopIdx) & ~0b0110000;

		if (num < 0 || num > 9)
		{
			digitNumber = "0";
		}
	}
}
