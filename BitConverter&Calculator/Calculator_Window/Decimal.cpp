#include "Decimal.h"

Decimal::Decimal()
{
	m_str_digitNumber = "0";
}

Decimal::Decimal(string str_num)
{
	SetNumber(str_num);
}

string Decimal::ConvertToBinary()
{
	bool b_negative = m_str_digitNumber.at(0) == '-';

	string str_result;
	string str_number = m_str_digitNumber;

	if (str_number == "0")
	{
		return "0";
	}

	if (b_negative)
	{
		str_number.erase(0, 1);
	}

	while (true)
	{
		int n_oneDigit = (str_number.at(str_number.length() - 1) & ~0b0110000);
		if (n_oneDigit % 2) 
		{
			str_result = "1" + str_result;
		}
		else
		{
			str_result = "0" + str_result;
		}

		if (str_number == "1")
		{
			break;
		}

		str_number = DigitOperator::Div(str_number, "2");
	}

	if (b_negative)
	{
		str_result = DigitOperator::GetTwoComplement(str_result);
		str_result = "1" + str_result;
	}
	else
	{
		str_result = "0" + str_result;
	}

	return str_result;
}

string Decimal::ConvertToDecimal()
{
	if (m_str_digitNumber[0] == '-')
	{
		m_str_digitNumber = "(" + m_str_digitNumber + ")";
	}

	return m_str_digitNumber;
}

string Decimal::ConvertToHexaDecimal()
{
	Binary bin(ConvertToBinary());

	return bin.ConvertToHexaDecimal();
}

void Decimal::SetNumber(string str_num)
{
	m_str_digitNumber = str_num;

	if (m_str_digitNumber[0] == '(' && m_str_digitNumber[m_str_digitNumber.length() - 1] == ')')
	{
		m_str_digitNumber.erase(m_str_digitNumber.length() - 1, 1);
		m_str_digitNumber.erase(0, 1);
	}

	int loopIdx = 0u;
	int number_len = m_str_digitNumber.length();
	if (m_str_digitNumber.at(0) == '-')
	{
		loopIdx++;
		number_len--;
	}

	for (; loopIdx < number_len; loopIdx++)
	{
		unsigned int num = m_str_digitNumber.at(loopIdx) & ~0b0110000;

		if (num < 0 || num > 9)
		{
			m_str_digitNumber = "0";
		}
	}
}
