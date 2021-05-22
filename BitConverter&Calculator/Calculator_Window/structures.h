#pragma once

typedef struct _parenthesis {
	_parenthesis()
	{
		opening_index = 0u;
		closing_index = 0u;
		priority = 0u;
	}

	_parenthesis(_parenthesis& other) 
	{
		opening_index = other.opening_index;
		closing_index = other.closing_index;
		priority = other.priority;
	}

	size_t opening_index;
	size_t closing_index;

	size_t priority;
} parenthesis_t;

typedef struct {
	parenthesis_t paren_info;
	char ch;
} stack_t;