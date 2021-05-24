#include "BitCalculatorMachine.h"

BitCalculatorMachine::BitCalculatorMachine()
{
}

string BitCalculatorMachine::Calculation(string strExpression)
{
    if (strExpression.length() == 0)
    {
        return "0";
    }

    if (strExpression.find('.') != string::npos)
    {
        return "0";
    }

    strExpression = '(' + strExpression + ')';

    ParenthesisMgr parenthesisMgr;
    parenthesis_t* parenthesisInfoArray[ParenthesisMgr::MAX_PAREN] = {};
    memset(parenthesisInfoArray, 0, sizeof(parenthesis_t*) * ParenthesisMgr::MAX_PAREN);

    /*checking parenthesis position*/
    parenthesisMgr.Get_matching_parentheses(parenthesisInfoArray, strExpression);

    for (int i = 0; i < ParenthesisMgr::MAX_PAREN; i++)
    {
        if (!parenthesisInfoArray[i])
        {
            break;
        }

        size_t start = parenthesisInfoArray[i]->opening_index;
        size_t sub_expr_len = parenthesisInfoArray[i]->closing_index - start + 1;

        string strSub_expr = strExpression.substr(start, sub_expr_len);

        Calculator* cal = new Calculator(strSub_expr);
        strSub_expr = cal->Calculate();
        delete cal;

        for (size_t j = 0; j < sub_expr_len; j++)
        {
            if (strSub_expr.length() > j)
            {
                strExpression[start++] = strSub_expr[j];
            }
            else
            {
                strExpression[start++] = ' ';
            }
        }
    }

    /*free memory of parenthesis*/
    for (int i = 0; i < ParenthesisMgr::MAX_PAREN; i++)
    {
        if (parenthesisInfoArray[i])
        {
            delete parenthesisInfoArray[i];
        }
    }

    /*erase unnecessary letters of answer*/
    strExpression.erase(remove_if(strExpression.begin(), strExpression.end(), [](const char ch) {
        return ch == '(' || ch == ')' || ch == ' ';
    }), strExpression.end());

    /*Erase unnecessary 0 letters,
    for example, if answer is 0011000, this makes it 11000*/
    for (size_t i = 0; i < strExpression.length(); i++)
    {
        if (strExpression.at(i) == '0' && strExpression.length() != 1)
        {
            strExpression.erase(0, 1);
        }
        else
        {
            break;
        }
    }

    return strExpression;
}
