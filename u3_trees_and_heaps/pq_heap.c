#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 10

typedef struct node
{
    int data, priority;
} Node;

// Inside main - static array (not global)
// Node priority_queue[HEAP_SIZE];

// Inserting into priority_queue
void pq_insert(Node *heap, int data, int priority, int *pn)
{
    int child, parent;

    Node temp;
    temp.data = data;
    temp.priority = priority;

    // Add new node to end of the heap
    heap[*pn] = temp;
    ++(*pn);

    // Last node is the child node
    child = *pn - 1;
    // Parent node
    parent = (child - 1) / 2;

    // Bottom up
    while ((child > 0) && temp.priority < heap[parent].priority)
    {
        heap[child] = heap[parent];
        child = parent;
        parent = (child - 1) / 2;
    }
    heap[child] = temp;
}

// Delete the top node
Node pq_delete(Node *heap, int *pn)
{
    Node temp = heap[0];
    heap[0] = heap[*pn-1];
    --(*pn);
    adjust(heap, *pn);
    return temp;
}

// Adjust the heap
void adjust(Node *heap, int n) {
    int child, parent;
    Node key;
    parent = 0;
    key = heap[parent];

    child = 2 * parent + 1;

    // If left child exists
    while (child < n) {
        // If right child exists
        if (child + 1 < n) {
            // If right node is greater than left
            if (heap[child + 1].priority < heap[child].priority){
                ++child;
            }
        }

        // Now child stores the index of the greater child
        if (key.priority > heap[child].priority) {
            heap[parent] = heap[child];
            parent = child;
            child = 2 * parent + 1;
        }
        else {
            break;
        }
    }
    heap[parent] = key;    
}
