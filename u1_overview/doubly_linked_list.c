#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next, *prev;
} Node;


/* 
To-Do
1. Create a struct for linked list 
2. Create node 
3. Insert node
    a. at front 
    b. at back 
    c. at intermediate position 
4. Remove node
    a. at front 
    b. at back 
    c. at intermediate position 
5. Traverse and display list  
6. Make choice based menu 
*/

Node* insertFront(Node* head, int data) {
    Node* block = (Node*) malloc(sizeof(Node));    
    block->data = data; 
    block->next = head;
    head->prev = block;

    return block;
}

Node* insertBack(Node* head, int data) {
    Node* block = (Node*) malloc(sizeof(Node));
    block->data = data;
    block->prev = head;
    head->next = block;

    return head;
}

Node* insertAtPosition(Node* head, int data, int pos) {
    Node* block = (Node*) malloc(sizeof(Node));
    block->data = data;

    Node* traverse = head;
    for (int i = 0; i< pos-1; i++) {
        traverse = traverse->next;
    }
    block->next = traverse->next;
    traverse->next->prev = block;
    traverse->next = block;
    block->prev = traverse;

    return head;
}

Node* deleteFront(Node* head) {
    Node* temp = head;
    head = head->next;    
    head->prev = NULL;
    free(temp);
    return head;
}

Node* deleteBack(Node* head) {
    Node* traverser = head;
    while (traverser->next->next != NULL) {
        traverser = traverser->next;
    }
    free(traverser->next);
    traverser->next = NULL; 
    return head;
}

Node* deleteAtPosition(Node* head, int pos) {
    Node* traverser = head;
    for (int i = 0; i < pos; i++) {
        if (traverser->next != NULL) 
            traverser = traverser->next;
        else 
            printf("IndexError: Position out of range");
    }
}

void display(Node* head) {
    Node* traverser = head;
    while (traverser->next != NULL) {
        traverser = traverser->next;
        printf("%d->\n", traverser->data);
    }
}

int main() {
    Node* head = (Node*) malloc(sizeof(Node));
    head->next = NULL;
    head->prev = NULL;

    return 0;
}