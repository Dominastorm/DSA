#include <stdio.h>
#include <stdlib.h>

// Node data structure
typedef struct node
{
    int data;
    struct node *left, *right;
} Node;

// Tree data structure
typedef struct tree
{
    Node *root;
} Tree;

void lex_insert(Tree *tree, int data)
{
    Node *new_node = create_node(data);

    if (tree->root == NULL)
    {
        tree->root = new_node;
        return;
    }

    Node *temp = tree->root;

    while (1)
    {
        if (data < temp->data)
        {
            if (temp->left == NULL)
            {
                temp->left = new_node;
                return;
            }
            else {
                temp = temp->left;
            }
        }
        else {
            if (temp->right == NULL) {
                temp->right = new_node;
                return;
            }
            else {
                temp = temp->right;
            }
        }
  }
}

#define STACK_SIZE 50

// Inorder traversal
void iter_inorder(Tree *tree) {
    Node *stack[STACK_SIZE];
    int top = -1;

    // set temp as root 
    Node *temp = tree->root;
    
    // start traversal in the left subtree
    while (top != -1 || temp != NULL) {
        // keep going left until you reach the leaf node
        while (temp != NULL) {
            push(stack, temp, &top);
            temp = temp->left;
        }
        // move to the right subtree and pop the elements stored in the stack
        temp = pop(stack, &top);
        printf("%d ", temp->data);
        temp = temp->right;
    }
    printf("\n");
}

// Preorder Traversal 
void iter_preorder(Tree *tree) {
    Node *stack[STACK_SIZE];
    int top = -1;

    // set temp as root 
    Node *temp = tree->root;

    // push root into the stack
    push(stack, temp, &top);

    while (top != -1) {
        // pop and print the element at the top of the stack
        temp = pop(stack, top);
        printf("%d ", temp->data);
        
        // Right child is pushed first so that
        // left child is processed first
        if (temp->right != NULL) {
            push(stack, temp->right, &top);
        }

        if (temp->left != NULL) {
            push(stack, temp->left, &top);
        }
    }
    printf("\n");
}

// Postorder Traversal
void iter_postorder(Tree *tree) {
    Node *s1[STACK_SIZE], *s2[STACK_SIZE];
    int t1 = -1, t2 = -1;
    
    // set temp as root;
    Node *temp = tree->root;
    push(s1, temp, &t1);

    while (t1 != -1) {
        // pop from first stack
        temp = pop(s1, &t1);

        // push into second stack
        push(s2, temp, &t2);

        // push left node into first stack
        if (temp->left != NULL) {
            push(s1, temp->left, &t1);
        }

        // push right node into the first stack
        if (temp->right != NULL) {
            push(s1, temp->right, &t1);
        }
    }

    while (t2 != -1) {
        temp = pop(s2, &t2);
        printf("%d ", temp  ->data);
    }
    print("\n");
}