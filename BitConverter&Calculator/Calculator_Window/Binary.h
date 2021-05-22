#pragma once
#include "IDigitNumber.h"
#include "DigitOperator.h"

class Binary :
    public IDigitNumber
{
public:
    Binary();
    Binary(string str_num);

public:
    virtual string ConvertToBinary() override;
    virtual string ConvertToDecimal() override;
    virtual string ConvertToHexaDecimal() override;
    
    virtual void SetNumber(string str_num) override;

private:
    char GetHexByBinary(string binary);
};

