#include <stdio.h>
#include <stdlib.h>

/* 
To-Do
1. Create a struct for linked list ✓
2. Create node ✓
3. Insert node
    a. at front ✓
    b. at back ✓
    c. at intermediate position ✓
4. Remove node
    a. at front ✓
    b. at back ✓
    c. at intermediate position ✓
5. Traverse and display list
*/

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* insertFront(Node *head, int data) {
    Node* block = (Node*) malloc(sizeof(Node));
    block->data = data;
    block->next = head;
    head = block;
    return head;
}

Node* insertBack(Node *head, int data) {
    Node* block = (Node*) malloc(sizeof(Node));
    block->data = data;

    Node* traverser = head;
    
    while (traverser->next != NULL) {
        traverser = traverser->next;
    }
    traverser->next = block;
    block->next = NULL;
    return head;
}

Node* insertAtPosition(Node *head, int data, int pos) {
    Node* block = (Node*) malloc(sizeof(Node));
    block->data = data;

    Node* traverser = head;

    for (int i = 0; i < pos-1; i++) {
        if (traverser->next != NULL) 
            traverser = traverser->next;
        else
            printf("IndexError: Position out of range!\n");
    }

    block->next = traverser->next;
    traverser->next = block;

    return head;
}

Node* deleteFront(Node *head) {
    // if list is empty
    if (head->next == NULL) {
        printf("List is empty!\n");
        return head;
    }
    // if list is not empty
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

Node* deleteBack(Node *head) {
    // if list is empty
    if (head->next == NULL) {
        printf("List is empty!\n");
        return head;
    }
    // If list is not empty
    Node* traverser = head;
    while (traverser->next->next != NULL) 
        traverser  = traverser->next;
    free(traverser->next);
   traverser->next = NULL;
   return head;
}

Node* deleteAtPosition(Node *head, int pos) {
    Node *traverser = head;
    for (int i = 0; i < pos-1; i++) {
        if (traverser->next != NULL)
            traverser = traverser->next; 
        else 
            printf("IndexError: Index out of range");
            return head;
    }
    Node* temp = traverser->next;
    traverser->next = traverser->next->next;
    free(temp);
    return head;
}

int main() {
    Node* head = (Node*) malloc(sizeof(Node));
    head = insertBack(head, 1);
    head = insertBack(head, 2);
    head = insertBack(head, 3);
    head = insertBack(head, 4);
    head = insertBack(head, 5);
    // head = insertAtPosition(head, 5, 6);
    head = deleteAtPosition(head, 2);
    // printf("%d\n", head->data);
    printf("%d\n", head->next->data);
    printf("%d\n", head->next->next->data);
    printf("%d\n", head->next->next->next->data);
    printf("%d\n", head->next->next->next->next->data);
    // choice to select what to do


    return 0;
}
