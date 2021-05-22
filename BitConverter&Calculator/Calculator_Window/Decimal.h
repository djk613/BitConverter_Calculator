#pragma once
#include "IDigitNumber.h"
#include "DigitOperator.h"
#include "Binary.h"

class Decimal :
    public IDigitNumber
{
public:
    Decimal();
    Decimal(string str_num);

    virtual string ConvertToBinary() override;
    virtual string ConvertToDecimal() override;
    virtual string ConvertToHexaDecimal() override;

    virtual void SetNumber(string str_num) override;
};

