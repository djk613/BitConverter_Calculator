#include "Calculator.h"

string Calculator::m_str_expr = "";
int Calculator::n_token_count = 0;



Calculator::Calculator(string expression)
{
	this->m_str_expr = expression;
	this->m_str_expr.erase(remove_if(this->m_str_expr.begin(), this->m_str_expr.end(), [](const char ch) {
		return ch == '(' || ch == ')' || ch == ' ';
	}), this->m_str_expr.end());

	CheckNegativeUnary();

	n_token_count = 0;
}

Calculator::~Calculator()
{
	delete m_ps;

	for (int i = 0; i < 300; i++) 
	{
		if (m_tokens[i])
		{
			delete m_tokens[i];
		}
	}
}

string Calculator::Calculate()
{
	if (Lexical())
	{
		if (Syntax())
		{
			Parsing();
			PostOrderView();

			string answer = Processing();

			if (answer.at(0) == '-') 
			{
				return '(' + answer + ')';
			}
			else
			{
				return answer;
			}
		}
		else 
		{
			cout << "Wrong Syntax";
			return "0";
		}
	}
	else
	{
		cout << "Wrong Lexical" << endl;
		return "0";
	}
}

int Calculator::MakeOperator(size_t i)
{
	m_tokens[n_token_count] = new Operator(m_str_expr.at(i));

	/*unary negative check
	operators like *-, /-, +-, --, can be managed here..
	but recommanding using parenthesis with unary operator*/
	if (m_str_expr[i + 1] == '-')
	{
		m_str_expr.erase(i + 1, 1);
		static_cast<Operator*>(m_tokens[n_token_count])->m_bRightValueNegative = true;
	}

	n_token_count++;

	return i + 1;
}

int Calculator::MakeOperand(size_t i)
{
	size_t startIdx, endIdx;  
	startIdx = i;

	while (IsDigit(m_str_expr.at(i)) || IsBinarySystem(m_str_expr.at(i)) || IsHexaSystem(m_str_expr.at(i)))
	{
		i++;

		if (m_str_expr.length() <= i)
		{
			break;
		}
	}

	endIdx = i;

	string str = m_str_expr.substr(startIdx, (endIdx - startIdx));

	m_tokens[n_token_count++] = new Operand(str);

	return endIdx;
}

int Calculator::Lexical()
{
	size_t i = 0;
	while (m_str_expr.at(i))
	{
		if (IsOperator(m_str_expr.at(i)))
		{
			i = MakeOperator(i);
		}

		else
		{
			if (IsDigit(m_str_expr.at(i)) || IsBinarySystem(m_str_expr.at(i)) || IsHexaSystem(m_str_expr.at(i)))
			{
				i = MakeOperand(i);
			}
			else
			{
				return false;
			}
		}

		if (m_str_expr.length() <= i)
		{
			break;
		}
	}

	return true;
}

bool Calculator::Syntax()
{
	if (n_token_count % 2 == 0)
	{
		return false;
	}

	if (m_tokens[0]->m_nPriority != 3)
	{
		return false;
	}

	for (int i = 1; i < n_token_count; i += 2)
	{
		if (m_tokens[i]->m_nPriority == 3)
		{
			return false;
		}
		if (m_tokens[i + 1]->m_nPriority != 3)
		{
			return false;
		}
	}

	return true;
}

void Calculator::Parsing()
{
	m_ps = new ParserTree(m_tokens[0]);

	for (int i = 1; i < n_token_count; i++)
	{
		m_ps->Add(m_tokens[i]);
	}
}

void Calculator::PostOrderView()
{
	m_ps->View();
}

string Calculator::Processing()
{
	return m_ps->Calculate();
}

void Calculator::CheckNegativeUnary()
{ 
	if (m_str_expr.at(0) == '-' && isdigit(m_str_expr.at(1)))
	{
		m_str_expr = "0" + m_str_expr;
	}
}

bool Calculator::IsOperator(char ch)
{
	return (ch == '+') | (ch == '-') | (ch == '*') | (ch == '/');
}

bool Calculator::IsDigit(char ch)
{
	return (ch >= '0') && (ch <= '9');
}

bool Calculator::IsBinarySystem(char ch)
{
	return (ch == 'B') || (ch == 'b');
}

bool Calculator::IsHexaSystem(char ch)
{
	return (ch == 'x') || (ch == 'X') 
		|| (ch == 'a') || (ch == 'A')
		|| (ch == 'b') || (ch == 'B')
		|| (ch == 'c') || (ch == 'C')
		|| (ch == 'd') || (ch == 'D')
		|| (ch == 'e') || (ch == 'E')
		|| (ch == 'f') || (ch == 'F');
}


