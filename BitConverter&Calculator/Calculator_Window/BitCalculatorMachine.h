#pragma once

#include <iostream>
#include "Binary.h"
#include "Decimal.h"
#include "DigitOperator.h"
#include "HexaDecimal.h"
#include "Calculator.h"
#include "ParenthesisMgr.h"
#include "structures.h"

class BitCalculatorMachine
{
public:
	BitCalculatorMachine();


public:
	string Calculation(string expression);

};

