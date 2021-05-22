#pragma once

#include "Includes.h"

class IDigitNumber 
{
public:
	virtual string ConvertToBinary() = 0;
	virtual string ConvertToDecimal() = 0;
	virtual string ConvertToHexaDecimal() = 0;

	virtual void SetNumber(string str_num) = 0;
	string GetNumber();

protected:
	string digitNumber;
};
