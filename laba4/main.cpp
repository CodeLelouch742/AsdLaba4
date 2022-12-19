#include "ArithmeticExpressionTree.h"

using namespace std;

struct node {
    int key;
    struct node *left, *right, *parent;
};

struct node *newNode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

struct node* search(struct node* root, int key) {
    if (root == NULL)
        return NULL;
    else if (root->key == key)
        return root;
    else if (root->key < key)
        return search(root->right, key);
    else
        return search(root->left, key);
};

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " -> ";
        inorder(root->right);
    }
}

struct node *insert(struct node *node, int key) {

    if (node == NULL) return newNode(key);

    if (key < node->key){
        node->left = insert(node->left, key);
        node->left->parent = node;
    }
    else{
        node->right = insert(node->right, key);
        node->right->parent = node;
    }
    return node;
}

struct node *minValueNode(struct node *node) {
    struct node *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

const node* maxElementInTree(const node* tr) {
    if (tr == NULL)
        return NULL;

    const node* p = tr;
    while (p->right != NULL)
        p = p->right;
    return p;
}

void printForvard(node *root)
{
    if(root)
    {
        printf("%i ",root->key);
        printForvard(root->left);
        printForvard(root->right);
    }
}

void printSymmetry(node *root)
{
    if(root)
    {
        printSymmetry(root->left);
        printf("%i ",root->key);
        printSymmetry(root->right);
    }
}

void printBack(node *root)
{
    if(root)
    {
        printBack(root->left);
        printBack(root->right);
        printf("%i ",root->key);
    }
}

void printWidth(node* root)
{
    if (root == NULL) return;
    queue<node*> t;
    t.push(root);

    while (!t.empty())
    {
        node* temp = t.front();
        t.pop();
        cout << temp->key << " ";

        if (temp->left != NULL)
            t.push(temp->left);

        if (temp->right != NULL)
            t.push(temp->right);
    }
}

const node* minElementInTree(const node* tr) {
    if (tr == NULL)
        return NULL;

    const node* p = tr;
    while (p->left != NULL)
        p = p->left;
    return p;
}

struct node *deleteNode(struct node *root, int key) {

    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int findNextElements(struct node *root, int key){

    root = search(root,key);
    struct node* parentRoot = root->parent;
    if(root->right != NULL)
        return minElementInTree(root->right)->key;
    else{
        while (parentRoot != NULL && root == parentRoot->right){
            root = parentRoot;
            parentRoot = parentRoot->parent;
        }
        return parentRoot->key;
    }
}

int findLastElements(struct node *root, int key){

    root = search(root,key);

    struct node* parentRoot = root->parent;
    if(root->left != NULL)
        return minElementInTree(root->left)->key;
    else{
        while (parentRoot != NULL && root == parentRoot->left){
            root = parentRoot;
            parentRoot = parentRoot->parent;
        }
        return parentRoot->key;
    }
}

void printTree(node * p,int level)
{
    if(p)
    {
        printTree(p->right,level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        cout << p->key << endl;
        printTree(p->left,level + 1);
    }
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    struct node *root = NULL;
    root = insert(root, 5);
    root = insert(root, 94);
    root = insert(root, 45);
    root = insert(root, 1);
    root = insert(root, 59);
    root = insert(root, 32);
    root = insert(root, 8);
    root = insert(root, 70);
    root = insert(root, 21);

    cout << "Вывод бинарного дерева" << endl;
    printTree(root,0);
    cout << endl;

    cout << "Поиск элемента с значением 32:\t";
    if(search(root,32))
        cout << "Элемент найден\n";
    cout << endl;

    cout << "Прямой обход:\t";
    printForvard(root);
    cout << endl << "Центрированный обход:\t";
    printSymmetry(root);
    cout << endl << "Обратный обход:\t";
    printBack(root);
    cout << endl << "Обход в ширину:\t";
    printWidth(root);
    cout<<endl;


    cout << endl << "Вывод следующего элемента после 5:\t" << findNextElements(root,5) << endl;
    cout << "Вывод предыдущего элемента до 8:\t" << findLastElements(root,8) << endl;

    cout << endl << "Отсортированное дерево: ";
    inorder(root);
    cout << endl;

    cout << "\nДерево после удаление 59\n";
    root = deleteNode(root, 59);
    printTree(root,0);

    cout << "\nВывод максимального значения в дереве - ";
    const node* pmax = maxElementInTree(root);
    if (pmax != NULL)
        cout << pmax->key << endl;

    cout << "Вывод минимального значения в дереве - ";
    const node* pmin = minElementInTree(root);
    if (pmin != NULL)
        cout << pmin->key << endl;
    cout << endl;

    cout << "--------------------------------------------------------------------------------" << endl;

    int form = 0;
    string expression, postfix;
    cout << "Формы для ввода: \n";
    cout << "1 - Префиксная\n";
    cout << "2 - Инфиксная\n";
    cout << "3 - Постфиксная\n";

    cout << "Введите номер формы для ввода -  ";
    cin >> form;

    cout << "\nВведите выражение:";
    cin >> expression;


    switch (form) {
        case 1:
        {
            string prefix = prefixToPostfix(expression);
            Node* root = formation(prefix);
            printTree(root,0);

            cout << "\nИнфиксное выражение: ";
            infixForm(root);

            cout << "\nПостфиксное выражение: ";
            postfixForm(root);

            cout << endl;
            system("pause");
        }
        case 2:
        {
            string postfix = infixToPostfix(expression);
            Node* root = formation(postfix);
            printTree(root,0);

            cout << "\nПрефиксное выражение: ";
            prefixForm(root);

            cout << "\nПостфиксное выражение: ";
            postfixForm(root);

            cout << endl;
            system("pause");
        }
        case 3:
        {
            Node* root = formation(expression);
            printTree(root,0);

            cout << "\nПрефиксное выражение:";
            prefixForm(root);

            cout << "\nИнфиксное выражение:  ";
            infixForm(root);

            cout << endl;
            system("pause");
        }

    }
}