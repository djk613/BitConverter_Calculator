#include "DigitOperator.h"

string DigitOperator::Add(string str_num1, string str_num2)
{
    bool b_num1Signed = IsSigned(str_num1);
    bool b_num2Signed = IsSigned(str_num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(str_num1, false);
    SetSign(str_num2, false);

    /*Erase unnecessary 0*/
    Trim(str_num1);
    Trim(str_num2);

    /*Algorithm works based on the condition that num1 is bigger than num2*/
    string* str_biggerOne = Compare(str_num1, str_num2) > 0 ? &str_num1 : &str_num2;

    string str_result;

    if (b_num1Signed == b_num2Signed) 
    {
        str_result = Sum(str_num1, str_num2);

        SetSign(str_result, b_num1Signed);
    }
    else
    {
        str_result = Difference(str_num1, str_num2);

        if (str_biggerOne == &str_num1)
        {
            SetSign(str_result, b_num1Signed);
        }
        else
        {
            SetSign(str_result, b_num2Signed);
        }
    }

    return str_result;
}

string DigitOperator::Sub(string str_num1, string str_num2)
{
    if (Compare(str_num1, str_num2) == 0)
    {
        return "0";
    }

    bool b_num1Signed = IsSigned(str_num1);
    bool b_num2Signed = IsSigned(str_num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(str_num1, false);
    SetSign(str_num2, false);

    /*Erase unnecessary 0*/
    Trim(str_num1);
    Trim(str_num2);

    /*Algorithm works based on the condition that num1 is bigger than num2*/
    string* str_biggerOne = Compare(str_num1, str_num2) > 0 ? &str_num1 : &str_num2;

    string str_result;

    if (b_num1Signed != b_num2Signed)
    {
        str_result = Sum(str_num1, str_num2);

        SetSign(str_result, b_num1Signed);
    }
    else 
    {
        str_result = Difference(str_num1, str_num2);
        Trim(str_result);

        if (str_biggerOne == &str_num1)
        {
            
            SetSign(str_result, b_num1Signed);
        }
        else
        {
            SetSign(str_result, !b_num2Signed);
        }
    }

    return str_result;
}

string DigitOperator::Mul(string str_num1, string str_num2)
{
    bool b_num1Signed = IsSigned(str_num1);
    bool b_num2Signed = IsSigned(str_num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(str_num1, false);
    SetSign(str_num2, false);

    Trim(str_num1);
    Trim(str_num2);

    string str_result;

    str_result = Multiply(str_num1, str_num2);
    Trim(str_result);

    SetSign(str_result, !(b_num1Signed == b_num2Signed));

    return str_result;
}

string DigitOperator::Div(string str_num1, string str_num2)
{
    bool b_num1Signed = IsSigned(str_num1);
    bool b_num2Signed = IsSigned(str_num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(str_num1, false);
    SetSign(str_num2, false);

    if (str_num2.compare("0") == 0)
    {
        return "0";
    }

    if (Compare(str_num1, str_num2) < 0)
    {
        return "0";
    }

    Trim(str_num1);
    Trim(str_num2);

    string str_result;

    str_result = Divide(str_num1, str_num2);
    Trim(str_result);

    SetSign(str_result, !(b_num1Signed == b_num2Signed));

    return str_result;
}

string DigitOperator::GetTwoComplement(string str_binary)
{
    string str_result;

    for (size_t i = 0; i < str_binary.length(); i++)
    {
        if (str_binary.at(i) & ~0b0110000)
        {
            str_result += "0";
        }
        else
        {
            str_result += "1";
        }
    }

    for (size_t i = str_result.length() - 1; i > 0; i--)
    {
        if ((str_result.at(i) & ~0b0110000) == 0b1)
        {
            str_result.at(i) = '0';
            continue;
        }

        str_result.at(i) = '1';
        break;
    }

    str_result = SetOverflowOnComplement(str_result);

    return str_result;
}

/*b_signed - true - negative
b_signed - false - positive*/
void DigitOperator::SetSign(string& str_number, bool b_sign)
{
    bool b_isSigned = IsSigned(str_number);

    if (b_isSigned == true && b_sign == false)
    {
        str_number.erase(0, 1);
    }
    else if (b_isSigned == false && b_sign == true)
    {
        str_number = '-' + str_number;
    }
}

bool DigitOperator::IsSigned(string str_number)
{
    if (str_number.length() == 0)
    {
        return false;
    }

    if (str_number.at(0) == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*simple function for making sum between two numbers that are positive*/
string DigitOperator::Sum(string str_num1, string str_num2)
{
    string str_result;

    SetNumbersForUseOnOperator(str_num1, str_num2);

    int n_overDigit = 0;

    for (size_t i = 0; i < str_num1.length(); i++)
    {
        int num = (str_num1.at(i) & ~0b0110000) + (str_num2.at(i) & ~0b0110000) + n_overDigit;
        n_overDigit = (num / 10);
        str_result += ((num % 10) | 0b0110000);
    }

    if (n_overDigit)
    {
        str_result += "1";
    }

    reverse(str_result.begin(), str_result.end());

    return str_result;
}

/*yielding numbers that is diffence between two positive numbers*/
string DigitOperator::Difference(string str_num1, string str_num2)
{
    string str_result;

    SetNumbersForUseOnOperator(str_num1, str_num2);

    int n_overDigit = 0;

    for (size_t i = 0; i < str_num1.length(); i++)
    {
        int num = (str_num1.at(i) & ~0b0110000) - (str_num2.at(i) & ~0b0110000) + n_overDigit;

        /*if num is negative*/
        if (num < 0)
        {
            n_overDigit = -1;
            num += 10;
        }
        else 
        {
            n_overDigit = 0;
        }

        str_result += (num | 0b0110000);
    }

    reverse(str_result.begin(), str_result.end());

    return str_result;
}

/*this multiply function works based on add funtion.
numerous results from add function makes results of multiply */
string DigitOperator::Multiply(string str_num1, string str_num2)
{
    string str_result;

    SetNumbersForUseOnOperator(str_num1, str_num2);

    string str_mulSum = "";
    int n_overDigit = 0;

    /*way of operating here is multiplying whole digits of the num1 with num2's each element*/
    for (size_t i = 0; i < str_num1.length(); i++)
    {
        if ((str_num1.at(i) & ~0b0110000) == 0)
        {
            /*if element 0, this element will not be multiplied and skipped,
            but exponent is necessary for this exception and mulSum has to be get *10 */
            str_mulSum += "0";
            continue;
        }

        for (size_t j = 0; j < str_num2.length(); j++)
        {
            /*if element 0, this element will not be multiplied and skipped*/
            if ((str_num2.at(j) & ~0b0110000) == 0)
            {
                continue;
            }

            int n_num = (str_num1.at(i) & ~0b0110000) * (str_num2.at(j) & ~0b0110000) + n_overDigit;
            n_overDigit = (n_num / 10);
            str_mulSum += ((n_num % 10) | 0b0110000);
        }

        str_mulSum += (n_overDigit | 0b0110000);
        reverse(str_mulSum.begin(), str_mulSum.end());

        str_result = Add(str_result, str_mulSum);

        str_mulSum = "";
        n_overDigit = 0;

        for (size_t k = 0; k <= i; k++)
        {
            /*This part is for applying exponent to result*/
            str_mulSum += "0";
        }
    }

    return str_result;
}

/*Divide funtion works based on subtract operation.
numerous subtraction action makes divide's results*/
string DigitOperator::Divide(string str_num1, string str_num2)
{
    string str_result;

    int n_num1_exponent = str_num1.length();
    int n_num2_exponent = str_num2.length();

    int n_difference_exponent = n_num1_exponent - n_num2_exponent;
    
    string str_numerator = str_num1;
    string str_dominator;

    for (int i = 0; i < n_num1_exponent; i++)
    {
        str_dominator = str_num2;

        if (Compare(str_numerator, str_dominator) < 0)
        {
            /*end of calculation, when left number is smaller than dominator, 
            but exponent shold be applied after it*/
            for (int j = 0; j <= n_difference_exponent - i; j++)
            {
                str_result += "0";
            }

            break;
        }

        for (int j = 0; j < n_difference_exponent - i; j++)
        {
            /*dominator exponent.. this function tries to do the superior digit part first*/
            str_dominator += "0";
        }

        for (int k = 0; k < 10; k++) 
        {
            string str_temp = str_numerator;
            str_numerator = Sub(str_numerator, str_dominator);/*subtract part*/

            if (IsSigned(str_numerator))
            {
                /*if numberator(lefted number) is negative, calculation moves to the next digit part*/
                str_numerator = str_temp;
                str_result += to_string(k);
                break;
            }
        }  
    }

    return str_result;
}

/*erase unnecessary 0parts*/
void DigitOperator::Trim(string& str_number)
{
    if ((str_number.length() > 1) && str_number.at(0) == '0')
    {
        int n_countZero = 0;
        
        while (str_number[++n_countZero] == '0')
        {
        }

        str_number.erase(0, n_countZero);
    }
}

int DigitOperator::Compare(string str_num1, string str_num2)
{
    if (str_num1.length() > str_num2.length())
    {
        return 1;
    }
    else if (str_num1.length() < str_num2.length())
    {
        return -1;
    }

    for (size_t i = 0; i < str_num1.length(); i++)
    {
        if (str_num1.at(i) > str_num2.at(i))
        {
            return 1;
        }
        else if (str_num1.at(i) < str_num2.at(i))
        {
            return -1;
        }
    }

    return 0;
}

/*The function has meaning of the function for structure*/
void DigitOperator::SetNumbersForUseOnOperator(string& str_num1, string& str_num2)
{
    /*Bigger number need to be num1 for simplifying algorithm*/
    if (Compare(str_num1, str_num2) < 0)
    {
        string str_temp = str_num1;
        str_num1 = str_num2;
        str_num2 = str_temp;
    }

    /*This algorithm calculation starts at array's 0 index element 
    and 0 index element means one digit and 1 index means tenth digit*/
    reverse(str_num1.begin(), str_num1.end());
    reverse(str_num2.begin(), str_num2.end());

    size_t n_number_length = str_num1.length() > str_num2.length() ? str_num1.length() : str_num2.length();

    /*Sum and Difference fuction need comparing numbers whole elements,
    so lower number's string will be filling with 0
    ex. 1241-> 124100000 vs 000000001*/
    for (size_t i = str_num1.length(); i < n_number_length; i++)
    {
        str_num1 += "0";
    }

    for (size_t i = str_num2.length(); i < n_number_length; i++)
    {
        str_num2 += "0";
    }
}

string DigitOperator::SetOverflowOnComplement(string str_number)
{
    for (size_t i = 0; i < str_number.length(); i++)
    {
        if (str_number.at(i) == '1')
        {
            return str_number;
        }
    }

    str_number.at(0) = '1';
    return str_number;
}
