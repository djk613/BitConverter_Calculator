#include "HexaDecimal.h"

HexaDecimal::HexaDecimal()
{
	digitNumber = "0";
}

HexaDecimal::HexaDecimal(string str_num)
{
	SetNumber(str_num);
}

string HexaDecimal::ConvertToBinary()
{
	string number = digitNumber;

	string result;

	for (size_t i = 0; i < number.length(); i++) 
	{
		result += GetBinaryByHex(number.at(i));
	}

	while (result.at(0) == '0' && result.at(1) == '0')
	{
		result.erase(0, 1);
	}

	return result;
}

string HexaDecimal::ConvertToDecimal()
{
	Binary binary(ConvertToBinary());

	return binary.ConvertToDecimal();
}

string HexaDecimal::ConvertToHexaDecimal()
{
	return digitNumber;
}

void HexaDecimal::SetNumber(string str_num)
{
	digitNumber = str_num;

	for (size_t i = 0; i < str_num.length(); i++)
	{
		unsigned int num = str_num.at(i);

		if (((num > 0b1000000 && num < 0b1000111) ||
			(num > 0b1100000 && num < 0b1100111) ||
			(num >= 0b110000 && num <= 0b111001)) == false)
		{
			digitNumber = "0";
		}
	}
}

string HexaDecimal::GetBinaryByHex(char hex)
{
	if (hex == '0')
	{
		return "0000";
	}
	else if (hex == '1')
	{
		return "0001";
	}
	else if (hex == '2')
	{
		return "0010";
	}
	else if (hex == '3')
	{
		return "0011";
	}
	else if (hex == '4')
	{
		return "0100";
	}
	else if (hex == '5')
	{
		return "0101";
	}
	else if (hex == '6')
	{
		return "0110";
	}
	else if (hex == '7')
	{
		return "0111";
	}
	else if (hex == '8')
	{
		return "1000";
	}
	else if (hex == '9')
	{
		return "1001";
	}
	else if (hex == 'A' || hex == 'a')
	{
		return "1010";
	}
	else if (hex == 'B' || hex == 'b')
	{
		return "1011";
	}
	else if (hex == 'C' || hex == 'c')
	{
		return "1100";
	}
	else if (hex == 'D' || hex == 'd')
	{
		return "1101";
	}
	else if (hex == 'E' || hex == 'e')
	{
		return "1110";
	}
	else if (hex == 'F' || hex == 'f')
	{
		return "1111";
	}

	return "0000";
}
