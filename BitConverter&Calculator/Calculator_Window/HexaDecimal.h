#pragma once
#include "IDigitNumber.h"
#include "Binary.h"

class HexaDecimal :
    public IDigitNumber
{
public:
    HexaDecimal();
    HexaDecimal(string str_num);

    virtual string ConvertToBinary() override;
    virtual string ConvertToDecimal() override;
    virtual string ConvertToHexaDecimal() override;

    virtual void SetNumber(string str_num) override;

private:
    string GetBinaryByHex(char hex);
};

