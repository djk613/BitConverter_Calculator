#include "Binary.h"

Binary::Binary()
{
	digitNumber = "0";
}

Binary::Binary(string str_num)
{
	SetNumber(str_num);
}

string Binary::ConvertToBinary()
{
	return digitNumber;
}

string Binary::ConvertToDecimal()
{
	string number = digitNumber;
	bool b_signed = (number.at(0) & ~0b0110000) == 1;

	/*erase signed bit cause it's not necessary anymore*/
	number.erase(0, 1);

	if (b_signed) 
	{
		number = DigitOperator::GetTwoComplement(number);
	}

	string result = "0";
	string twoMultiple = "1";

	for (int i = number.length() - 1; i >= 0; i--)
	{
		if ((number.at(i) & ~0b0110000) == 1) 
		{
			result = DigitOperator::Add(result, twoMultiple);
		}

		twoMultiple = DigitOperator::Mul(twoMultiple, "2");
	}

	if (b_signed) 
	{
		result = "(-" + result + ")";
	}

	return result;
}

string Binary::ConvertToHexaDecimal()
{
	string number = digitNumber;
	string sub_number;

	string result;

	while (number.length() > 4)
	{
		size_t start = number.length() - 4;

		sub_number = number.substr(start, 4);
		number.erase(start, 4);

		result = GetHexByBinary(sub_number) + result;
	}

	int n_left_number_len = number.length();

	for (int i = 0; i < 4 - n_left_number_len; i++)
	{
		number = "0" + number;
	}

	result = GetHexByBinary(number) + result;

	return result;
}

void Binary::SetNumber(string str_num)
{
	digitNumber = str_num;

	/*not need to check sign bit*/
	for (size_t i = 1; i < str_num.length(); i++)
	{
		unsigned int num = str_num.at(i) & ~0b0110000;

		if(num == 1)
		{
			return;
		}
	}

	digitNumber = "0";
}

char Binary::GetHexByBinary(string binary)
{
	if (binary == "0000")
	{
		return '0';
	}
	else if (binary == "0001")
	{
		return '1';
	}
	else if (binary == "0010")
	{
		return '2';
	}
	else if (binary == "0011")
	{
		return '3';
	}
	else if (binary == "0100")
	{
		return '4';
	}
	else if (binary == "0101")
	{
		return '5';
	}
	else if (binary == "0110")
	{
		return '6';
	}
	else if (binary == "0111")
	{
		return '7';
	}
	else if (binary == "1000")
	{
		return '8';
	}
	else if (binary == "1001")
	{
		return '9';
	}
	else if (binary == "1010")
	{
		return 'A';
	}
	else if (binary == "1011")
	{
		return 'B';
	}
	else if (binary == "1100")
	{
		return 'C';
	}
	else if (binary == "1101")
	{
		return 'D';
	}
	else if (binary == "1110")
	{
		return 'E';
	}
	else if (binary == "1111")
	{
		return 'F';
	}

	return '0';
}
