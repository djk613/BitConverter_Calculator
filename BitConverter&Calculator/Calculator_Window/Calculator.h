#pragma once
#include "Includes.h"
#include "Token.h"
#include "Operator.h"
#include "Operand.h"
#include "ParserTree.h"

class Calculator
{
public:
	Calculator(string expr);
	~Calculator();

	string Calculate();
	
	int MakeOperator(size_t i);
	int MakeOperand(size_t i);

private:
	int Lexical();
	bool Syntax();
	void Parsing();
	void PostOrderView();
	string Processing();
	
	void CheckNegativeUnary();

	bool IsOperator(char ch);
	bool IsDigit(char ch);
	bool IsBinarySystem(char ch);
	bool IsHexaSystem(char ch);

private:
	static string expr;
	static int n_token_count;

	Token* tokens[300] = { 0 };

	ParserTree* ps;
};

