#include "HexaDecimal.h"

HexaDecimal::HexaDecimal()
{
	m_str_digitNumber = "0";
}

HexaDecimal::HexaDecimal(string str_num)
{
	SetNumber(str_num);
}

string HexaDecimal::ConvertToBinary()
{
	string str_number = m_str_digitNumber;

	string str_result;

	for (size_t i = 0; i < str_number.length(); i++)
	{
		str_result += GetBinaryByHex(str_number.at(i));
	}

	while (str_result.at(0) == '0' && str_result.at(1) == '0')
	{
		str_result.erase(0, 1);
	}

	return str_result;
}

string HexaDecimal::ConvertToDecimal()
{
	Binary binary(ConvertToBinary());

	return binary.ConvertToDecimal();
}

string HexaDecimal::ConvertToHexaDecimal()
{
	return m_str_digitNumber;
}

void HexaDecimal::SetNumber(string str_num)
{
	m_str_digitNumber = str_num;

	for (size_t i = 0; i < str_num.length(); i++)
	{
		unsigned int num = str_num.at(i);

		if (((num > 0b1000000 && num < 0b1000111) ||
			(num > 0b1100000 && num < 0b1100111) ||
			(num >= 0b110000 && num <= 0b111001)) == false)
		{
			m_str_digitNumber = "0";
		}
	}
}

string HexaDecimal::GetBinaryByHex(char ch_hex)
{
	if (ch_hex == '0')
	{
		return "0000";
	}
	else if (ch_hex == '1')
	{
		return "0001";
	}
	else if (ch_hex == '2')
	{
		return "0010";
	}
	else if (ch_hex == '3')
	{
		return "0011";
	}
	else if (ch_hex == '4')
	{
		return "0100";
	}
	else if (ch_hex == '5')
	{
		return "0101";
	}
	else if (ch_hex == '6')
	{
		return "0110";
	}
	else if (ch_hex == '7')
	{
		return "0111";
	}
	else if (ch_hex == '8')
	{
		return "1000";
	}
	else if (ch_hex == '9')
	{
		return "1001";
	}
	else if (ch_hex == 'A' || ch_hex == 'a')
	{
		return "1010";
	}
	else if (ch_hex == 'B' || ch_hex == 'b')
	{
		return "1011";
	}
	else if (ch_hex == 'C' || ch_hex == 'c')
	{
		return "1100";
	}
	else if (ch_hex == 'D' || ch_hex == 'd')
	{
		return "1101";
	}
	else if (ch_hex == 'E' || ch_hex == 'e')
	{
		return "1110";
	}
	else if (ch_hex == 'F' || ch_hex == 'f')
	{
		return "1111";
	}

	return "0000";
}
