#include <stdio.h>
#include <stdlib.h>

// left_thread and right_thread are boolean values to indicate
// whether the left and right nodes are threads or not, respectively
typedef struct node {
    int data;
    struct node *left, *right;
    int left_thread, right_thread;
} Node;

typedef struct tree {
    Node *root;
} Tree;

// Insertion
void thread_insert(Tree *tree, int data) {
    Node *new_node = create_node(data);
    Node *temp = tree->root;

    // If the tree is empty, insert the new node
    if (temp == NULL) {
        tree->root = new_node;
        return;
    }

    // Search for position to insert and then break
    while (1) {
        if (data < temp->data) {
            if (temp->left_thread == 0) {
                temp = temp->left;
            }
            else {
                break;
            }
        }
        else {
            if (temp->right_thread == 0) {
                temp = temp->right;
            }
            else {
                break;
            }
        }
    }

    // Attach to either left or right 
    if (data < temp->data) {
        // Assign right_thread for new_node
        new_node->left = temp->left;
        new_node->right = temp;

        temp->left_thread = 0;
        temp->left = new_node;
    }
    else {
        // Assign left_thread for new_node
        new_node->right = temp->right;
        new_node->left = temp;

        temp->right_thread = 0;
        temp->right = new_node;
    }
}

// Find the inorder successor of the current node
Node *inorder_successor(Node *root) {
    // if the tree is empty (this is not even possible, idk why you need this condition)
    if (root == NULL) {
        return NULL;
    }
    
    // if the tree has a right thread
    if (root->right_thread == 1) {
        root = root->right;
    }
    // go to the right subtree of current node and find the leftmost node
    else {
        root = root->right;
        while (root->left != NULL && root->left_thread == 0) {
            root = root->left;
        }
    }
    return root;
}

// Inorder traversal
void thread_inorder(Tree *tree) {
    Node *temp = tree->root;

    if (temp == NULL) {
        printf("Empty tree\n");
        return;
    } 

    // Go to leftmost node
    while (temp->left_thread == 0) {
        temp = temp->left;
    }

    // Print inorder successors
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = inorder_successor(temp);
    }
}