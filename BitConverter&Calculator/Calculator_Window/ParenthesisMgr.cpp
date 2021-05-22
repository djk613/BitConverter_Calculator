#include "ParenthesisMgr.h"

size_t ParenthesisMgr::Get_matching_parentheses(parenthesis_t** parentheses, string str)
{
    char ch;
    size_t paren_index;
    size_t str_index;
    size_t result_index;
    stack_t stack;
    parenthesis_t paren;
    parenthesis_t* result[MAX_PAREN] = {};
    stack_t stack_array[MAX_STACK] = {};
    size_t stack_count;
    size_t idx;
    size_t str_len;

    paren_index = 0u;
    str_index = 0u;
    result_index = 0u;
    stack_count = 0u;
    str_len = str.length();

    while (str.at(str_index) != '\0')
    {
        ch = str.at(str_index);

        if (ch == '(') 
        {

            paren.opening_index = str_index;
            paren.closing_index = 0xffffffff;
            paren.priority = stack_count;

            stack.paren_info = paren;
            stack.ch = ch;

            Push(stack_array, &stack_count, stack);
            result[result_index++] = new parenthesis_t(paren);

        }
        else if (ch == ')') 
        {

            stack = Get(stack_array, &stack_count);

            if (stack.ch == '(' && ch == ')') 
            {
                Pop(stack_array, &stack_count);
                stack.paren_info.closing_index = str_index;

                parentheses[paren_index++] = new parenthesis_t(stack.paren_info);
            }
        }

        str_index++;

        if(str_len <= str_index)
        {
            break;
        }
    }

    stack_count = 0u;

    Synchronize_and_delete_array(parentheses, result, result_index, paren_index);
    Ordering(parentheses);

    return paren_index;
}

void ParenthesisMgr::Push(stack_t* stack_array, size_t* stack_count, stack_t stack)
{
    if (*stack_count > MAX_STACK)
    {
        return;
    }

    stack_array[(*stack_count)++] = stack;
}

char ParenthesisMgr::Is_stack_empty(size_t* stack_count)
{
    return (*stack_count == 0);
}

stack_t ParenthesisMgr::Pop(stack_t* stack_array, size_t* stack_count)
{
    stack_t null_stack;

    if (Is_stack_empty(stack_count)) 
    {
        null_stack.ch = '\0';
        return null_stack;
    }

    return stack_array[--(*stack_count)];
}

stack_t ParenthesisMgr::Get(stack_t* stack_array, size_t* stack_count)
{
    stack_t null_stack;

    if (Is_stack_empty(stack_count)) 
    {
        null_stack.ch = '\0';
        return null_stack;
    }

    return stack_array[*stack_count - 1];
}

void ParenthesisMgr::Synchronize_and_delete_array(parenthesis_t** parentheses,
    parenthesis_t** result, 
    size_t count, 
    size_t count_paren)
{
    size_t i;
    size_t j;
    size_t idx;
    size_t priority;

    for (i = 0u; i < count; i++) 
    {
        idx = result[i]->opening_index;

        for (j = 0u; j < count_paren; j++) 
        {
            if (idx == parentheses[j]->opening_index) 
            {
                result[i]->closing_index = parentheses[j]->closing_index;
            }
        }
    }

    /*free memories of uncessary data*/
    for (i = 0u, j = 0u; i < count; i++) 
    {
        if (result[i]->closing_index != 0xffffffff) 
        {
            delete parentheses[j];
            parentheses[j++] = result[i];
        }
    }
}

/*ordering by priority*/
void ParenthesisMgr::Ordering(parenthesis_t** parentheses)
{
    //c++ style
    //stl vector is used here for using sort algorithm.

    vector<parenthesis_t*> tempList;

    int idx = 0;
    while (true) 
    {
        if (parentheses[idx] == NULL)
        {
            break;
        }

        tempList.emplace_back(parentheses[idx++]);
    }

    //c++ lamda.. becareful if using this at lower version complier. 
    sort(tempList.begin(), tempList.end(), [](const parenthesis_t* left, const parenthesis_t* right) {
        return left->priority > right->priority;
    });

    for (idx = 0; idx < tempList.size(); idx++) 
    {
        parentheses[idx] = tempList.at(idx);
    }

    tempList.clear();
}
