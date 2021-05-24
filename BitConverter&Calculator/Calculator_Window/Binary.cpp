#include "Binary.h"

Binary::Binary()
{
	m_str_digitNumber = "0";
}

Binary::Binary(string str_num)
{
	SetNumber(str_num);
}

string Binary::ConvertToBinary()
{
	return m_str_digitNumber;
}

string Binary::ConvertToDecimal()
{
	string str_number = m_str_digitNumber;
	bool b_signed = (str_number.at(0) & ~0b0110000) == 1;

	/*erase signed bit cause it's not necessary anymore*/
	str_number.erase(0, 1);

	if (b_signed) 
	{
		str_number = DigitOperator::GetTwoComplement(str_number);
	}

	string str_result = "0";
	string str_twoMultiple = "1";

	for (int i = str_number.length() - 1; i >= 0; i--)
	{
		if ((str_number.at(i) & ~0b0110000) == 1)
		{
			str_result = DigitOperator::Add(str_result, str_twoMultiple);
		}

		str_twoMultiple = DigitOperator::Mul(str_twoMultiple, "2");
	}

	if (b_signed) 
	{
		str_result = "(-" + str_result + ")";
	}

	return str_result;
}

string Binary::ConvertToHexaDecimal()
{
	string str_number = m_str_digitNumber;
	string str_sub_number;

	string str_result;

	while (str_number.length() > 4)
	{
		size_t start = str_number.length() - 4;

		str_sub_number = str_number.substr(start, 4);
		str_number.erase(start, 4);

		str_result = GetHexByBinary(str_sub_number) + str_result;
	}

	int n_left_number_len = str_number.length();

	for (int i = 0; i < 4 - n_left_number_len; i++)
	{
		str_number = "0" + str_number;
	}

	str_result = GetHexByBinary(str_number) + str_result;

	return str_result;
}

void Binary::SetNumber(string str_num)
{
	m_str_digitNumber = str_num;

	/*not need to check sign bit*/
	for (size_t i = 1; i < str_num.length(); i++)
	{
		unsigned int num = str_num.at(i) & ~0b0110000;

		if(num == 1)
		{
			return;
		}
	}

	m_str_digitNumber = "0";
}

char Binary::GetHexByBinary(string str_binary)
{
	if (str_binary == "0000")
	{
		return '0';
	}
	else if (str_binary == "0001")
	{
		return '1';
	}
	else if (str_binary == "0010")
	{
		return '2';
	}
	else if (str_binary == "0011")
	{
		return '3';
	}
	else if (str_binary == "0100")
	{
		return '4';
	}
	else if (str_binary == "0101")
	{
		return '5';
	}
	else if (str_binary == "0110")
	{
		return '6';
	}
	else if (str_binary == "0111")
	{
		return '7';
	}
	else if (str_binary == "1000")
	{
		return '8';
	}
	else if (str_binary == "1001")
	{
		return '9';
	}
	else if (str_binary == "1010")
	{
		return 'A';
	}
	else if (str_binary == "1011")
	{
		return 'B';
	}
	else if (str_binary == "1100")
	{
		return 'C';
	}
	else if (str_binary == "1101")
	{
		return 'D';
	}
	else if (str_binary == "1110")
	{
		return 'E';
	}
	else if (str_binary == "1111")
	{
		return 'F';
	}

	return '0';
}
