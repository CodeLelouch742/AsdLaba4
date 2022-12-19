#include <iostream>
#include <Windows.h>
#include <queue>
#include <stack>
#include <string>

using namespace std;

class Node
{
public:
    char key;
    Node* left, * right;

    Node(char key)
    {
        this->key = key;
        this->left = this->right = NULL;
    };

    Node(char key, Node* left, Node* right)
    {
        this->key = key;
        this->left = left;
        this->right = right;
    };
};

void printTree(Node * p,int level)
{
    if(p)
    {
        printTree(p->right,level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        cout << p->key << endl;
        printTree(p->left,level + 1);
    }
}

bool isOperator(char sign) {
    return (sign == '+' || sign == '-' || sign == '*' || sign == '/' || sign == '^');
}

bool isOperand(char operand) {
    return (operand >= '0' && operand <= '9');
}

int priority(char sign)
{
    if (sign == '*' || sign == '/') {
        return 3;
    }

    if (sign == '+' || sign == '-') {
        return 4;
    }

    if (sign == '^') {
        return 5;
    }

    return INT_MAX;
}


string infixToPostfix(string infix)
{
    stack<char> stack;

    string postfix;

    for (char sign : infix)
    {
        if (sign == '(') {
            stack.push(sign);
        }

        else if (sign == ')')
        {
            while (stack.top() != '(')
            {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }

        else if (isOperand(sign)) {
            postfix.push_back(sign);
        }

        else {
            while (!stack.empty() && priority(sign) >= priority(stack.top()))
            {
                postfix.push_back(stack.top());
                stack.pop();
            }

            stack.push(sign);
        }
    }

    while (!stack.empty())
    {
        postfix.push_back(stack.top());
        stack.pop();
    }

    return postfix;
}

string prefixToPostfix(string prefix)
{

    stack<string> stack;

    int length = prefix.size();

    for (int i = length - 1; i >= 0; i--)
    {
        if (isOperator(prefix[i]))
        {
            string operand1 = stack.top();
            stack.pop();
            string operand2 = stack.top();
            stack.pop();

            string temp = operand1 + operand2 + prefix[i];

            stack.push(temp);
        }

        else {
            stack.push(string(1, prefix[i]));
        }
    }

    return stack.top();
}

Node* formation(string postfix)
{
    if (postfix.length() == 0) {
        return NULL;
    }

    stack<Node*> stack;

    for (char sign : postfix)
    {
        if (isOperator(sign))
        {
            Node* right = stack.top();
            stack.pop();

            Node* left = stack.top();
            stack.pop();

            Node* node = new Node(sign, left, right);

            stack.push(node);
        }

        else {
            stack.push(new Node(sign));
        }
    }

    return stack.top();
}

void prefixForm(Node* root)
{
    if (root == NULL) {
        return;
    }
    cout << root->key;
    prefixForm(root->left);
    prefixForm(root->right);
}

void postfixForm(Node* root)
{
    if (root == NULL) {
        return;
    }

    postfixForm(root->left);
    postfixForm(root->right);
    cout << root->key;
}

void infixForm(Node* root)
{
    if (root == NULL) {
        return;
    }

    if (isOperator(root->key)) {
        cout << "(";
    }

    infixForm(root->left);
    cout << root->key;
    infixForm(root->right);

    if (isOperator(root->key)) {
        cout << ")";
    }
}
