#pragma once
#include "Token.h"
#include "IDigitNumber.h"
#include "Binary.h"
#include "Decimal.h"
#include "HexaDecimal.h"

class Operand : public Token
{
public:
	Operand(string number);

	virtual void View();

public:
	IDigitNumber* value;
};

