#include "DigitOperator.h"

string DigitOperator::Add(string num1, string num2)
{
    bool b_num1Signed = IsSigned(num1);
    bool b_num2Signed = IsSigned(num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(num1, false);
    SetSign(num2, false);

    /*Erase unnecessary 0*/
    Trim(num1);
    Trim(num2);

    /*Algorithm works based on the condition that num1 is bigger than num2*/
    string* biggerOne = Compare(num1, num2) > 0 ? &num1 : &num2;

    string result;

    if (b_num1Signed == b_num2Signed) 
    {
        result = Sum(num1, num2);

        SetSign(result, b_num1Signed);
    }
    else
    {
        result = Difference(num1, num2);

        if (biggerOne == &num1)
        {
            SetSign(result, b_num1Signed);
        }
        else
        {
            SetSign(result, b_num2Signed);
        }
    }

    return result;
}

string DigitOperator::Sub(string num1, string num2)
{
    if (Compare(num1, num2) == 0)
    {
        return "0";
    }

    bool b_num1Signed = IsSigned(num1);
    bool b_num2Signed = IsSigned(num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(num1, false);
    SetSign(num2, false);

    /*Erase unnecessary 0*/
    Trim(num1);
    Trim(num2);

    /*Algorithm works based on the condition that num1 is bigger than num2*/
    string* biggerOne = Compare(num1, num2) > 0 ? &num1 : &num2;

    string result;

    if (b_num1Signed != b_num2Signed)
    {
        result = Sum(num1, num2);

        SetSign(result, b_num1Signed);
    }
    else 
    {
        result = Difference(num1, num2);
        Trim(result);

        if (biggerOne == &num1)
        {
            
            SetSign(result, b_num1Signed);
        }
        else
        {
            SetSign(result, !b_num2Signed);
        }
    }

    return result;
}

string DigitOperator::Mul(string num1, string num2)
{
    bool b_num1Signed = IsSigned(num1);
    bool b_num2Signed = IsSigned(num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(num1, false);
    SetSign(num2, false);

    Trim(num1);
    Trim(num2);

    string result;

    result = Multiply(num1, num2);
    Trim(result);

    SetSign(result, !(b_num1Signed == b_num2Signed));

    return result;
}

string DigitOperator::Div(string num1, string num2)
{
    bool b_num1Signed = IsSigned(num1);
    bool b_num2Signed = IsSigned(num2);

    /*erase sign and will be attached after this algorithm if it has sign*/
    SetSign(num1, false);
    SetSign(num2, false);

    if (num2.compare("0") == 0) 
    {
        return "0";
    }

    if (Compare(num1, num2) < 0) 
    {
        return "0";
    }

    Trim(num1);
    Trim(num2);

    string result;

    result = Divide(num1, num2);
    Trim(result);

    SetSign(result, !(b_num1Signed == b_num2Signed));

    return result;
}

string DigitOperator::GetTwoComplement(string binary)
{
    string result;

    for (size_t i = 0; i < binary.length(); i++)
    {
        if (binary.at(i) & ~0b0110000)
        {
            result += "0";
        }
        else
        {
            result += "1";
        }
    }

    for (size_t i = result.length() - 1; i > 0; i--)
    {
        if ((result.at(i) & ~0b0110000) == 0b1)
        {
            result.at(i) = '0';
            continue;
        }

        result.at(i) = '1';
        break;
    }

    result = SetOverflowOnComplement(result);

    return result;
}

/*b_signed - true - negative
b_signed - false - positive*/
void DigitOperator::SetSign(string& number, bool b_sign)
{
    bool isSigned = IsSigned(number);

    if (isSigned == true && b_sign == false) 
    {
        number.erase(0, 1);
    }
    else if (isSigned == false && b_sign == true) 
    {
        number = '-' + number;
    }
}

bool DigitOperator::IsSigned(string number)
{
    if (number.length() == 0) 
    {
        return false;
    }

    if (number.at(0) == '-') 
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*simple function for making sum between two numbers that are positive*/
string DigitOperator::Sum(string num1, string num2)
{
    string result;

    SetNumbersForUseOnOperator(num1, num2);

    int n_overDigit = 0;

    for (size_t i = 0; i < num1.length(); i++)
    {
        int num = (num1.at(i) & ~0b0110000) + (num2.at(i) & ~0b0110000) + n_overDigit;
        n_overDigit = (num / 10);
        result += ((num % 10) | 0b0110000);
    }

    if (n_overDigit)
    {
        result += "1";
    }

    reverse(result.begin(), result.end());

    return result;
}

/*yielding numbers that is diffence between two positive numbers*/
string DigitOperator::Difference(string num1, string num2)
{
    string result;

    SetNumbersForUseOnOperator(num1, num2);

    int n_overDigit = 0;

    for (size_t i = 0; i < num1.length(); i++)
    {
        int num = (num1.at(i) & ~0b0110000) - (num2.at(i) & ~0b0110000) + n_overDigit;

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

        result += (num | 0b0110000);
    }

    reverse(result.begin(), result.end());

    return result;
}

/*this multiply function works based on add funtion.
numerous results from add function makes results of multiply */
string DigitOperator::Multiply(string num1, string num2)
{
    string result;

    SetNumbersForUseOnOperator(num1, num2);

    string mulSum = "";
    int n_overDigit = 0;

    /*way of operating here is multiplying whole digits of the num1 with num2's each element*/
    for (size_t i = 0; i < num1.length(); i++)
    {
        if ((num1.at(i) & ~0b0110000) == 0)
        {
            /*if element 0, this element will not be multiplied and skipped,
            but exponent is necessary for this exception and mulSum has to be get *10 */
            mulSum += "0";
            continue;
        }

        for (size_t j = 0; j < num2.length(); j++)
        {
            /*if element 0, this element will not be multiplied and skipped*/
            if ((num2.at(j) & ~0b0110000) == 0)
            {
                continue;
            }

            int num = (num1.at(i) & ~0b0110000) * (num2.at(j) & ~0b0110000) + n_overDigit;
            n_overDigit = (num / 10);
            mulSum += ((num % 10) | 0b0110000);
        }

        mulSum += (n_overDigit | 0b0110000);
        reverse(mulSum.begin(), mulSum.end());

        result = Add(result, mulSum);

        mulSum = "";
        n_overDigit = 0;

        for (size_t k = 0; k <= i; k++)
        {
            /*This part is for applying exponent to result*/
            mulSum += "0";
        }
    }

    return result;
}

/*Divide funtion works based on subtract operation.
numerous subtraction action makes divide's results*/
string DigitOperator::Divide(string num1, string num2)
{
    string result;

    int n_num1_exponent = num1.length();
    int n_num2_exponent = num2.length();

    int n_difference_exponent = n_num1_exponent - n_num2_exponent;
    
    string numerator = num1;
    string dominator;

    for (int i = 0; i < n_num1_exponent; i++)
    {
        dominator = num2;

        if (Compare(numerator, dominator) < 0)
        {
            /*end of calculation, when left number is smaller than dominator, 
            but exponent shold be applied after it*/
            for (int j = 0; j <= n_difference_exponent - i; j++)
            {
                result += "0";
            }

            break;
        }

        for (int j = 0; j < n_difference_exponent - i; j++)
        {
            /*dominator exponent.. this function tries to do the superior digit part first*/
            dominator += "0";
        }

        for (int k = 0; k < 10; k++) 
        {
            string temp = numerator;
            numerator = Sub(numerator, dominator);/*subtract part*/

            if (IsSigned(numerator))
            {
                /*if numberator(lefted number) is negative, calculation moves to the next digit part*/
                numerator = temp;
                result += to_string(k);
                break;
            }
        }  
    }

    return result;
}

/*erase unnecessary 0parts*/
void DigitOperator::Trim(string& number)
{
    if ((number.length() > 1) && number.at(0) == '0')
    {
        int n_countZero = 0;
        
        while (number[++n_countZero] == '0')
        {
        }

        number.erase(0, n_countZero);
    }
}

int DigitOperator::Compare(string num1, string num2)
{
    if (num1.length() > num2.length()) 
    {
        return 1;
    }
    else if (num1.length() < num2.length())
    {
        return -1;
    }

    for (size_t i = 0; i < num1.length(); i++) 
    {
        if (num1.at(i) > num2.at(i))
        {
            return 1;
        }
        else if (num1.at(i) < num2.at(i)) 
        {
            return -1;
        }
    }

    return 0;
}

/*The function has meaning of the function for structure*/
void DigitOperator::SetNumbersForUseOnOperator(string& num1, string& num2)
{
    /*Bigger number need to be num1 for simplifying algorithm*/
    if (Compare(num1, num2) < 0) 
    {
        string temp = num1;
        num1 = num2;
        num2 = temp;
    }

    /*This algorithm calculation starts at array's 0 index element 
    and 0 index element means one digit and 1 index means tenth digit*/
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    size_t number_length = num1.length() > num2.length() ? num1.length() : num2.length();

    /*Sum and Difference fuction need comparing numbers whole elements,
    so lower number's string will be filling with 0
    ex. 1241-> 124100000 vs 000000001*/
    for (size_t i = num1.length(); i < number_length; i++)
    {
        num1 += "0";
    }

    for (size_t i = num2.length(); i < number_length; i++)
    {
        num2 += "0";
    }
}

string DigitOperator::SetOverflowOnComplement(string number)
{
    for (size_t i = 0; i < number.length(); i++)
    {
        if (number.at(i) == '1')
        {
            return number;
        }
    }

    number.at(0) = '1';
    return number;
}
