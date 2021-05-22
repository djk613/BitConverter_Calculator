#include "BitCalculatorMachine.h"

BitCalculatorMachine::BitCalculatorMachine()
{
}

string BitCalculatorMachine::Calculation(string expr)
{
    if (expr.length() == 0) 
    {
        return "0";
    }

    if (expr.find('.') != string::npos) 
    {
        return "0";
    }

    expr = '(' + expr + ')';

    ParenthesisMgr mgr;
    parenthesis_t* infoArray[ParenthesisMgr::MAX_PAREN] = {};
    memset(infoArray, 0, sizeof(parenthesis_t*) * ParenthesisMgr::MAX_PAREN);

    /*checking parenthesis position*/
    mgr.Get_matching_parentheses(infoArray, expr);

    for (int i = 0; i < ParenthesisMgr::MAX_PAREN; i++)
    {
        if (!infoArray[i])
        {
            break;
        }

        size_t start = infoArray[i]->opening_index;
        size_t sub_expr_len = infoArray[i]->closing_index - start + 1;

        string sub_expr = expr.substr(start, sub_expr_len);

        Calculator* cal = new Calculator(sub_expr);
        sub_expr = cal->Calculate();
        delete cal;

        for (size_t j = 0; j < sub_expr_len; j++)
        {
            if (sub_expr.length() > j)
            {
                expr[start++] = sub_expr[j];
            }
            else
            {
                expr[start++] = ' ';
            }
        }
    }

    /*free memory of parenthesis*/
    for (int i = 0; i < ParenthesisMgr::MAX_PAREN; i++)
    {
        if (infoArray[i])
        {
            delete infoArray[i];
        }
    }

    /*erase unnecessary letters of answer*/
    expr.erase(remove_if(expr.begin(), expr.end(), [](const char ch) {
        return ch == '(' || ch == ')' || ch == ' ';
    }), expr.end());

    /*Erase unnecessary 0 letters,
    for example, if answer is 0011000, this makes it 11000*/
    for (size_t i = 0; i < expr.length(); i++)
    {
        if (expr.at(i) == '0' && expr.length() != 1)
        {
            expr.erase(0, 1);
        }
        else
        {
            break;
        }
    }

    return expr;
}
