/* 
             _ _     _____   _                                        _ 
 _   _ _ __ (_) |_  |___ /  | |_ _ __ ___  ___  ___    __ _ _ __   __| |
| | | | '_ \| | __|   |_ \  | __| '__/ _ \/ _ \/ __|  / _` | '_ \ / _` |
| |_| | | | | | |_   ___) | | |_| | |  __/  __/\__ \ | (_| | | | | (_| |
 \__,_|_| |_|_|\__| |____/   \__|_|  \___|\___||___/  \__,_|_| |_|\__,_|
                                                                        
 _                          
| |__   ___  __ _ _ __  ___ 
| '_ \ / _ \/ _` | '_ \/ __|
| | | |  __/ (_| | |_) \__ \
|_| |_|\___|\__,_| .__/|___/
                 |_|         
*/

#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------------------
// 01 - STRUCTURES FOR *TREE* AND *NODE*
// ----------------------------------------------------------------

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

// ----------------------------------------------------------------
// STRUCTURE HELPER FUNCTIONS
// ----------------------------------------------------------------

// Create a node
Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Initialise tree
Tree *init_tree()
{
    Tree *new_tree = (Tree *)malloc(sizeof(Tree));
    new_tree->root = NULL;
    return new_tree;
}

// Destroy all nodes
void destroy_nodes(Node *root)
{
    if (root == NULL)
        return;
    // If it is a leaf node, we can free it
    if (root->left == NULL && root->right == NULL)
    {
        free(root);
        return;
    }
    // if the node has a left child
    if (root->left != NULL)
        destroy_nodes(root->left);
    // if the node has a right child
    if (root->right != NULL)
        destroy_nodes(root->right);
}

// Destroy tree
void destroy_tree(Tree *tree)
{
    if (tree == NULL)
        return;
    destroy_nodes(tree->root);
    free(tree);
}

// Finding height of a tree
int height(Node *t)
{
    int l, r;

    // Empty tree
    if (t == NULL)
    {
        return -1;
    }

    // Single node tree
    if ((t->left == NULL) && (t->right == NULL))
    {
        return 0;
    }

    // Height of left subree
    l = height(t->left);

    // Height of right subtree
    r = height(t->right);

    // If left subtree is taller
    if (l > r)
    {
        return l + 1;
    }
    // If right subtree is taller
    else
    {
        return r + 1;
    }
}

// ----------------------------------------------------------------
// 02 - INSERTION INTO BINARY SEARCH TREE
// ----------------------------------------------------------------

/*
Process of inserting
1. If there is no root node -> insert root node
2. If there is a root node
    L. If the data is smaller than the root node -> traverse the left subtree 
        i. If the left subtree is empty -> insert node
        ii. If the left subtree is not empty -> Go to 2
    R. If the data is greater than (or equal to) the root node -> traverse the right subtree
        i. If the right subtree is empty -> insert node
        ii. If the right subtree is not empty -> Go to 2    
*/

// Recursive function
void lex_insert_leaf(Node *root, int data)
{

    // If the new data is less than the root node's data
    if (data < root->data)
    {

        // If the left subtree is empty -> insert node
        if (root->left == NULL)
        {
            Node *new_node = create_node(data);
            root->left = new_node;
        }

        // If the left subtree is not empty
        // -> Call function with left child as new root
        else
        {
            lex_insert_leaf(root->left, data);
        }
    }

    // If the new data is greater than (or equal to) the root node's data
    else
    {

        // If the left subtree is empty -> insert node
        if (root->right == NULL)
        {
            Node *new_node = create_node(data);
            root->right = new_node;
        }

        // If the right subtree is not empty
        // -> call function with right child as new root
        else
        {
            lex_insert_leaf(root->right, data);
        }
    }
}

// Function called once on Tree* datatype
void lex_insert(Tree *tree, int data)
{

    // If there are no root nodes, create the first node
    if (tree->root == NULL)
    {
        Node *new_node = create_node(data);
        tree->root = new_node;
        return;
    }

    // Otherwise, call the recursive function
    lex_insert_leaf(tree->root, data);
}

// ----------------------------------------------------------------
// 03 - TREE TRAVERSAL
// ----------------------------------------------------------------

// A - PREORDER TRAVERSAL

/*
1. Check if there is a root node in the tree
2. Print the root node's data
3. Traverse the left subtree
4. Traverse the right subtree
*/

// Recursive function
void preorder_leaves(Node *root)
{
    if (root != NULL)
    {
        // visit root node
        printf("%d ", root->data);

        // Traverse left subtree
        preorder_leaves(root->left);

        // Traverse right subtree
        preorder_leaves(root->right);
    }
}

// Function to be called once on Tree* datatype
void tree_preorder(Tree *tree)
{
    preorder_leaves(tree->root);
    printf("\n");
}

// B - INORDER TRAVERSAL

/*
1. Check if there is a root node in the tree
2. Traverse the left subtree
3. Print the root node's data
4. Traverse the right subtree
*/

// Recursive function
void inorder_leaves(Node *root)
{
    if (root != NULL)
    {
        // Traverse left subtree
        inorder_leaves(root->left);

        // visit root node
        printf("%d ", root->data);

        // Traverse right subtree
        inorder_leaves(root->right);
    }
}

// Function to be called once on Tree* datatype
void tree_inorder(Tree *tree)
{
    inorder_leaves(tree->root);
    printf("\n");
}

// C - POSTORDER TRAVERSAL

/*
1. Check if there is a root node in the tree
2. Traverse the left subtree
3. Traverse the right subtree
4. Print the root node's data
*/

// Recursive function
void postorder_leaves(Node *root)
{
    if (root != NULL)
    {
        // Traverse left subtree
        postorder_leaves(root->left);

        // Traverse right subtree
        postorder_leaves(root->right);
        
        // visit root node
        printf("%d ", root->data);
    }
}

// Function to be called once on Tree* datatype
void tree_postorder(Tree *tree)
{
    postorder_leaves(tree->root);
    printf("\n");
}

// ----------------------------------------------------------------
// 04 - MINIMUM VALUE, MAXIMUM VALUE, NUMBER OF NODES
// ----------------------------------------------------------------

// A - MINIMUM VALUE

int min_val_leaves(Node *root)
{
    // Return the data of the left most node
    if (root->left == NULL)
    {
        return root->data;
    }
    // Keep going left until you reach dead end
    return min_val_leaves(root->left);
}

// Minimum value -> left most node
int min_val(Tree *tree)
{
    // If the tree is empty
    if (tree->root == NULL)
    {
        return -1;
    }
    // Traverse left subtree
    return min_val_leaves(tree->root);
}

// B - MAXIMUM VALUE

int max_val_leaves(Node *root)
{
    // Return the data of the left most node
    if (root->right == NULL)
    {
        return root->data;
    }
    // Keep going right until you reach dead end
    return max_val_leaves(root->right);
}

// Maximum value -> right most node
int max_val(Tree *tree)
{
    // If the tree is empty
    if (tree->root == NULL)
    {
        return -1;
    }
    // Traverse right subtree
    return max_val_leaves(tree->root);
}

// C - NUMBER OF NODES

// Total number of nodes = 1 +
// number of nodes in left subtree +
// number of nodes in right subtree

int no_of_nodes_leaves(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + no_of_nodes_leaves(root->left) + no_of_nodes_leaves(root->right);
}

int no_of_nodes(Tree *tree)
{
    return no_of_nodes_leaves(tree->root);
}

// D - NUMBER OF LEAF NODES

// Total number of leaf nodes =
// number of leaf nodes in left subtree +
// number of leaf nodes in right subtree
int no_of_leaf_nodes_leaves(Node *root)
{
    // If the tree is empty
    if (root == NULL)
    {
        return 0;
    }

    // If it is leaf
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    return no_of_nodes_leaves(root->left) + no_of_leaf_nodes_leaves(root->right);
}

int no_of_leaf_nodes(Tree *tree)
{
    return no_of_leaf_nodes_leaves(tree->root);
}

// ----------------------------------------------------------------
// 05 - DELETE A NODE
// ----------------------------------------------------------------

void delete_node(Tree *tree, int value)
{
    Node *temp = tree->root, *parent = NULL,
         *grandchild = NULL, *inorder_succ = NULL;

    //  Search for a given node in a tree

    // If we haven't reached a leaf and the node is not found
    while (temp != NULL && temp->data != value)
    {

        parent = temp;

        // if value is greater than root node
        if (value > temp->data)
        {
            temp = temp->right;
        }

        // if value is smaller than root node
        else
        {
            temp = temp->left;
        }
    }

    // If value is not found in the tree
    if (temp == NULL)
    {
        printf("%d is not present in the tree\n", value);
        return;
    }

    // Temp has only one child (left)
    else if (temp->right == NULL)
    {
        grandchild = temp->left;
    }

    // Temp has only one child (right)
    else if (temp->left == NULL)
    {
        grandchild = temp->right;
    }

    // Temp has two children
    else
    {
        // Find the inorder successor (min. value in the right subtree)
        inorder_succ = temp->right;

        while (inorder_succ->left != NULL)
        {
            inorder_succ = inorder_succ->left;
        }

        // The left tree of temp gets attached to the inorder successor of temp
        inorder_succ->left = temp->left;

        // grandchild becomes temp->right
        grandchild = temp->right;
    }

    // Attach the grandchild

    // if we are deleting the root node
    if (parent == NULL)
    {
        tree->root = grandchild;
    }
    else if (temp == parent->right)
    {
        parent->right = grandchild;
    }
    else if (temp == parent->left)
    {
        parent->left = grandchild;
    }

    // Delete temp
    free(temp);
}

// ----------------------------------------------------------------
// 06 - BST USING ARRAYS
// ----------------------------------------------------------------

// A - TREE CREATION

#define TREE_SIZE 40

/*
int main() {
    int binary_tree[TREE_SIZE];
    bst_initialise(binary_tree);
    return 0;
}
*/

void bst_init(int *bst)
{
    for (int i = 0; i < TREE_SIZE; ++i)
    {
        bst[i] = -1;
    }
}

void bst_insert(int *bst, int data)
{
    int i = 0;

    // Empty tree
    if (bst[i] == -1)
    {
        bst[i] = data;
    }

    // Not empty tree
    else
    {
        while (i < TREE_SIZE && bst[i] != -1)
        {
            if (data < bst[i])
            {
                i = 2 * i + 1;
            }
            else
            {
                i = 2 * i + 2;
            }
        }
        if (i >= TREE_SIZE)
        {
            printf("Tree is full\n");
            return;
        }
        bst[i] = data;
    }
}

// B - TREE TRAVERSAL

// I - PREORDER

// is the root index of the iteration
void bst_preorder_helper(int *bst, int i)
{
    if (bst[i] != -1)
    {
        // Rootnode
        printf("%d ", bst[i]);

        // Left node
        bst_preorder_helper(bst, 2 * i + 1);

        // Right node
        bst_preorder_helper(bst, 2 * i + 2);
    }
}

void bst_preorder(int *bst)
{
    bst_preorder_helper(bst, 0);
}

// II - POSTORDER

// is the root index of the iteration
void bst_postorder_helper(int *bst, int i)
{
    if (bst[i] != -1)
    {
        // Rootnode
        printf("%d ", bst[i]);

        // Left node
        bst_postorder_helper(bst, 2 * i + 1);

        // Right node
        bst_postorder_helper(bst, 2 * i + 2);
    }
}

void bst_postorder(int *bst)
{
    bst_postorder_helper(bst, 0);
}

// III - INORDER

// is the root index of the iteration
void bst_inorder_helper(int *bst, int i)
{
    if (bst[i] != -1)
    {
        // Rootnode
        printf("%d ", bst[i]);

        // Left node
        bst_inorder_helper(bst, 2 * i + 1);

        // Right node
        bst_inorder_helper(bst, 2 * i + 2);
    }
}

void bst_inorder(int *bst)
{
    bst_inorder_helper(bst, 0);
}

// ----------------------------------------------------------------
// 07 - EXPRESSION TREE
// ----------------------------------------------------------------

// In different file - exp_tree.c

// ----------------------------------------------------------------
// 08 - ITERATIVE TREE TRAVERSAL
// ----------------------------------------------------------------

// In different file - iter_tree.c

// ----------------------------------------------------------------
// 09 - THREADED BST
// ----------------------------------------------------------------

// In different file - threaded_bst.c

// ----------------------------------------------------------------
// 10 - CONTRUCTING TREE FROM TRAVERSALS
// ----------------------------------------------------------------

// No code implementaion

// ----------------------------------------------------------------
// 11 - N-ary tree to Binary tree
// ----------------------------------------------------------------

// No code implementation

// ----------------------------------------------------------------
// 12 - Heap
// ----------------------------------------------------------------

// Max Heapify
// Array implementation -
// left child - 2*i+1
// right child - 2*i+2

void max_heapify(int *heap, int n)
{
    int key, child, parent, k;

    for (k = 1; k < n; ++k)
    {
        child = k;
        key = heap[child];

        // parent uses inverse of child formula 2*i+1
        parent = (child - 1) / 2;

        // keep going down and checking if the child
        // is greater than the parent
        while ((child > 0) && heap[parent] < key)
        {
            // replace the child with the parent
            heap[child] = heap[parent];

            // Go up
            child = parent;
            parent = (child - 1) / 2;
        }
        heap[child] = key;
    }
}

// Deleting the max node
// Swap the root node with the rightmost node and then readjust

// Function to adjust the heap after deleting the root node
// (More efficient than heapify)
void adjust(int *heap, int n)
{
    int child, parent, key;
    parent = 0;
    key = heap[parent];

    child = 2 * parent + 1;

    // If left child exists
    while (child < n)
    {

        // If right child exists
        if (child + 1 < n)
        {
            // If right node is greater than the left node
            if (heap[child + 1] > heap[child])
            {
                ++child;
            }
        }

        // Now child stores index of greater child
        if (key < heap[child])
        {
            heap[parent] = heap[child];
            parent = child;
            child = 2 * parent + 1;
        }
        else
        {
            break;
        }
        heap[parent] = key;
    }

// Priority Queue using Heap

// In separate file - pq_heap.c