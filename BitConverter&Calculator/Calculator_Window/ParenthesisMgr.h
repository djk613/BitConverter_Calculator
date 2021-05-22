#pragma once
#include "Includes.h"
#include "structures.h"

class ParenthesisMgr
{
public:
	size_t Get_matching_parentheses(parenthesis_t** parentheses, string str);

private:

	void Push(stack_t* stack_array, size_t* stack_count, stack_t stack);
	char Is_stack_empty(size_t* stack_count);
	stack_t Pop(stack_t* stack_array, size_t* stack_count);
	stack_t Get(stack_t* stack_array, size_t* stack_count);
	void Synchronize_and_delete_array (parenthesis_t** parentheses, parenthesis_t** result, size_t count, size_t count_paren);

	void Ordering(parenthesis_t** parentheses);

public:
	static constexpr int MAX_STACK = 256;
	static constexpr int MAX_PAREN = 256;
};

