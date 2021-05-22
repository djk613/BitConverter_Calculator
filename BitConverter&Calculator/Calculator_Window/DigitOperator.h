#pragma once

#include "Includes.h"

/*class helping for calculation operation between string to string with Decimal digit format*/
class DigitOperator
{
public:
	static string Add(string num1, string num2);
	static string Sub(string num1, string num2);
	static string Mul(string num1, string num2);
	static string Div(string num1, string num2);

	/*for toggling binary sign*/
	static string GetTwoComplement(string binary);

private:
	static void SetSign(string& number, bool b_sign);
	static bool IsSigned(string number);

	static string Sum(string num1, string num2);
	static string Difference(string num1, string num2);
	static string Multiply(string num1, string num2);
	static string Divide(string num1, string num2);

	static void Trim(string& number);
	static int Compare(string num1, string num2);

	/*this is converting numbers for using customized algorithm.
	It cannot be used anywhere.*/
	static void SetNumbersForUseOnOperator(string& num1, string& num2);

	static string SetOverflowOnComplement(string number);
};

