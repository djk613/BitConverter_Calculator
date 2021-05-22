#pragma once
#include "Token.h"
#include "Operator.h"
#include "Operand.h"

class ParserTree
{
public:
	typedef struct Node 
	{
		Token* token;
		Node* left;
		Node* right;
		Node(Token* token)
		{
			this->token = token;
			left = right = nullptr;
		}
	} Node_t;

public:
	ParserTree(Token* token);
	~ParserTree();

	void Add(Token* token);
	void PostOrder(Node_t* sr);
	void View();
	string Calculate();
	string PostOrderCalculate(Node_t* sr);

private:
	void DeleteAllChildNode(Node_t* node);

private:
	Node_t* root;
};

