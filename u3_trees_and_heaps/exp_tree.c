#include <stdio.h>
#include <stdlib.h>


// ----------------------------------------------------------------
// 07 - EXPRESSION TREE
// ----------------------------------------------------------------


// A - CONSTRUCTION

// Steps
// 1. Convert to Postfix
// 2. If character is an operand, push it onto stack
// 3. If character is an operator, create a node in the tree. Pop the
//    element from the stack and make it thte node's right child. Pop
//    the next element and make it the node's right child. Pop the next
//    selement from the stack and make it the node's left child.

#define STACK_SIZE 40

// Node data structure
typedef struct node
{
    char ch;
    struct node *left, *right;
} Node;

typedef struct tree {
    Node *root;
} Tree;

// Create a node
Node *create_node(char ch)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->ch = ch;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void create_exp_tree(Tree *tree, char *exp)
{
    char ch;
    Node *stack[STACK_SIZE];
    int top = -1;
    Node *temp = NULL;

    for (int i = 0; exp[i] != 0; ++i)
    {
        ch = exp[i];
        temp = create_node(ch);

        // If the char is an operator
        if (is_oper(ch))
        {

            // Pop the top two from stack
            temp->right = pop(stack, &top);
            temp->left = pop(stack, &top);

            // Push the operator to the stack
            push(stack, temp, &top);
        }

        // Otherwise, push operand to the stack
        else
        {
            push(stack, temp, &top);
        }
        tree->root = pop(stack, &top);
        stack_destroy(stack, top);
    }
}

int is_oper(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return 1;
    default:
        return 0;
    }
}

// B - TRAVERSAL

// I - PREORDER TRAVERSAL

void exp_preorder_helper(Node *root)
{
    if (root != NULL)
    {
        printf("%c ", root->ch);
        exp_preorder_helper(root->left);
        exp_preorder_helper(root->right);
    }
}

void exp_preorder(Tree *tree)
{
    exp_preorder_helper(tree->root);
    printf("\n");
}

// II - INORDER TRAVERSAL

void exp_inorder_helper(Node *root)
{
    if (root != NULL)
    {
        exp_inorder_helper(root->left);
        printf("%c ", root->ch);
        exp_inorder_helper(root->right);
    }
}

void exp_inorder(Tree *tree)
{
    exp_inorder_helper(tree->root);
    printf("\n");
}

// III - POSTORDER TRAVERSAL

void exp_postorder_helper(Node *root)
{
    if (root != NULL)
    {
        exp_postorder_helper(root->left);
        exp_postorder_helper(root->right);
        printf("%c ", root->ch);
    }
}

void exp_postorder(Tree *tree)
{
    exp_postorder_helper(tree->root);
    printf("\n");
}

// C - EVALUATION
int evaluate(Tree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return 0;
    return evaluate_helper(tree->root);
}

// Recursive function
int evaluate_helper(Node *root)
{
    int x;
    if (root == NULL)
        return 0;
    switch (root->ch)
    {
    case '+':
    {
        return evaluate_helper(root->left) + evaluate_helper(root->right);
    }
    case '-':
    {
        return evaluate_helper(root->left) - evaluate_helper(root->right);
    }
    case '^':
    {
        return powerof(evaluate_helper(root->left), evaluate_helper(root->right));
    }
    case '/':
    {
        return evaluate_helper(root->left) / evaluate_helper(root->right);
    }
    case '*':
    {
        return evaluate_helper(root->left) * evaluate_helper(root->right);
    }
    default:
    {
        printf("Enter the value of %c: root->ch");
        scanf("%d", &x);
        return x;
    }
    }
}

int powerof(int a, int b)
{
    int res = 1;
    for (int i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}
