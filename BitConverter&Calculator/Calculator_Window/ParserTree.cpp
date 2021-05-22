#include "ParserTree.h"

ParserTree::ParserTree(Token* token)
{
	root = new Node_t(token);
}

ParserTree::~ParserTree()
{
    DeleteAllChildNode(root);

    delete root;
}

void ParserTree::Add(Token* token)
{
    Node_t* now = new Node_t(token);

    Token* st = root->token;

    if (st->MoreThanPriority(token))
    {
        now->left = root;
        root = now;
    }
    else
    {
        /*if it is operator*/
        if (token->priority != 3)
        {
            now->left = root->right;
            root->right = now;
        }
        else
        {
            Node_t* pa = root;
            while (pa->right)
            {
                pa = pa->right;
            }
            pa->right = now;
        }
    }
}

void ParserTree::PostOrder(Node_t* sr)
{
    if (sr)
    {
        PostOrder(sr->left);
        PostOrder(sr->right);
        sr->token->View();
    }
}

void ParserTree::View()
{
    PostOrder(root);
    cout << endl;
}

string ParserTree::Calculate()
{
    return PostOrderCalculate(root);
}

string ParserTree::PostOrderCalculate(Node_t* sr)
{
    if (sr->left)
    {
        string lvalue = PostOrderCalculate(sr->left);
        string rvalue = PostOrderCalculate(sr->right);
        Operator* op = dynamic_cast<Operator*>(sr->token);

        if (op->m_bRightValueNegative)
        {
            rvalue = '-' + rvalue;
        }

        return op->operator_action(lvalue, rvalue);
    }

    Operand* op = dynamic_cast<Operand*>(sr->token);

    /*basically, operation process is running based on decimal system!*/
    return op->value->ConvertToDecimal();
}

void ParserTree::DeleteAllChildNode(Node_t* node)
{
    if (node->left) 
    {
        DeleteAllChildNode(node->left);
        
        delete node->left;
    }

    if (node->right) 
    {
        DeleteAllChildNode(node->right);

        delete node->right;
    }
}
