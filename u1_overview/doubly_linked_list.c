#include <stdio.h>
#include <stdlib.h>

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

typedef struct node {
    int data;
    struct node *next, *prev;
} Node;

Node* insertFront(Node* head, int data) {
    Node* block = (Node*) malloc(sizeof(Node));    
    block->data = data; 
    block->next = head;
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
    printf(" %d", head->data);
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }
    while(head->next != NULL) {
        head = head->next;
        printf(" -> %d", head->data);
    }
}



int main() {
    Node* head = NULL; 
    // choice based menu
    int choice;
    int data;
    int pos;
    while (1) {
        printf(
        "\nChoose the operation you want to perform\n"
        "1. Insert front\n"
        "2. Insert back\n"
        "3. Insert at position\n"
        "4. Delete front\n"
        "5. Delete back\n"
        "6. Delete at position\n"
        "7. Display\n"
        "0. Exit\n"
        );
    
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    // insert front
    if (choice == 1) {
        printf("Enter element to be inserted: ");
        scanf("%d", &data);
        head = insertFront(head, data);    
        printf("Element inserted\n Current list:");
        display(head);
    }
    // insert back
    else if (choice == 2) {
        printf("Enter element to be inserted: ");
        scanf("%d", &data);
        head = insertBack(head, data);
        display(head);
    }
    // insert at position
    else if (choice == 3) {
        printf("Enter element to be inserted: ");
        scanf("%d", &data);
        printf("Enter position to be inserted at: ");
        scanf("%d", &pos);
        head = insertAtPosition(head, data, pos);
        display(head);
    }
    // delete front
    else if (choice == 4) {
        head = deleteFront(head);
        display(head);
    }
    // delete back
    else if (choice == 5) {
        head = deleteBack(head);
        display(head);
    }
    // delete at position
    else if (choice == 6) {
        printf("Enter position to be deleted at: ");
        scanf("%d", &pos);
        head = deleteAtPosition(head, pos);
        display(head);
    }
    // traverse and display
    else if (choice == 7) {
        display(head);
    }
    // exit
    else 
        break;
    }
    return 0;
}