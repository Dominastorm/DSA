#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 50

// Creating the structure
typedef struct graph {
    int n; // number of vertices
    int adj[MAX_NODES][MAX_NODES]; // Adjacency Matrix
} Graph;

// Creating the graph
void create_graph(Graph *adj_mat) {
    int i, j;

    for (int i = 0; i < adj_mat->n; i++) {
        for (int j = 0; j < adj_mat->n; j) {
            adj_mat->adj[i][j] =0;
        }
    }
    
    while (1) {
        printf("Enter source and destination vertices:");
        scanf("%d %d", &i, &j);

        if(i < 0 && j <= 0 || i >= adj_mat->n || j >= adj_mat->n) {
            break;
        }

        adj_mat->adj[i][j] = 1;
    }
}

// Find indegree of node
int indegree(Graph *adj_mat, int v) {
    int count = 0;
    for (int i = 0; i < adj_mat->n; i ++i) {
        if (adj_mat->adj[i][v] == 1) {
            ++count;
        }
    }
    return count;
}

// Find outdegree of node
int outdegree(Graph *adj_mat, int v) {
    int count = 0;
    for (int i = 0; i < adj_mat->n; ++j) {
        if (adj_mat->adj[v][j] == 1) {
            ++count;
        }
    }
    return count;
}

// Adjacency list

#define MAX_NODES 50

typedef struct node {
    int data; /* Value of the column of the connection */
    struct node *next;
} Node;

/* Inside main(), initialise the array of nodes */
Node *adj_list[MAX_NODES];

// Creating a graph
// Creating the graph
void create_graph(Graph *adj_list[], int n) {
    int i, j;

    for (int i = 0; i < n; i++) {
        adj_list[i] = NULL; 
    }
    
    while (1) {
        printf("Enter source and destination vertices:");
        scanf("%d %d", &i, &j);

        if(i < 0 && j <= 0 || i >= n || j >= n) {
            break;
        }

        // both fro undirected
        insert(adj_list, i, j);
    }
}

// Finding outdegree
int outdegree(Node *adj_list[], int n, int v) {
    int count = 0;
    Node *traverse = adj_list[v];
    
    while (traverse != NULL) {
        ++count;
        traverse = traverse->next;
    }
    return count;
}

// Finding indegree
int indegree(Node *adj_list[], int n, int v) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        Node *traverse = adj_list[i];

        while (traverse != NULL) {
            if (traverse->data == v) {
                ++count;
            }
            traverse = traverse->next;
        }
    }
    return count;
}

// Insert helper function - insert to the end

void insert(Node *adj_list[], int i, int data) {
    Node* new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->data = data;

    Node * traverse = adj_list[i];

    if(traverse == NULL) {
        adj_list[i] = new_node;
        return; 
    }
    while (traverse->next != NULL) {
        traverse = traverse->next;
    }
    traverse->next = new_node;
}

// Graph traversal

void dfs_helper(Graph *adj_mat, int vertex, int *visited) {
    // Mark node as visited and display 
    visited[vertex] = 1;
    printf("%d", vertex);

    // Call dfs_helper function on all of its unvisited nodes
    for (int i = 0; i < adj_mat->n; i++) {
        if (adj_mat->adj[vertex][i] == 1 && visited[i] == 0) {
            dfs_helper(adj_mat, i, visited);
        }
    }
}

void dfs(Graph *adj_mat) {
    int vertex, *visited;

    // Accept user input
    printf("Enter source vertex: ");
    scanf("%d", &vertex);

    // Out of  bounds
    if (vertex < 0 || vertex >= adj_mat->n) {
        printf("out of bounds");
        return;
    }

    // Initialise visited list and set to 0s
    visited =(int*) calloc(adj_mat-n, sizeof(int));

    // Call recursicve function
    dfs_helper(adj_mat, vertex, visited);

    // Free memory used by visited 
    free(visited);
}

// Graph traversal for adjacaency list

void dfs_helper(Node *adj_list[], int vertex, int *visited) {
    // Maskr node as visited and display
    visited[vertex] = 1;
    printf("%d", vertex);

    Node *traverse = adj_list[vertex];
    
    while(traverse != NULL) {
        if (visited[traverse->data] == 0){
            dfs_helper(adj_list, traverse->data, visisted);
        }
        traverse = traverse->next;
    }
}

// dfs for adjacency list
void dfs(Node *adj_list[], int n) {
    int vertex, *visited;

    // Acceptuser input
    printf("Enter source vertex: ");
    scanf("%d", &vertex);

    // OUt of  bounds
    if (vertex< 0 || vertex >= n) {
        printf("Vertex not in graph");
        return;
    }

    // Initialise visitedlist
    visited= (int*)calloc(n, sizeof(int));

    // Call recursicve function
    dfs_helper(adj_list, vertex, visited);
    printf("\n");

    // free memory
    free(visited);
}

// graph traversal in adjaceency matrix

// Helper functions
void append(int *queue, int v, int *pqr) {
    ++(*pqr);
    queue[*pqr] = v;
}

int delete(int *queue, int *pqr) {
    int res = queue[0];
    
    for (int i = 0; i < *pqr; ++i) {
        queue[i] = queue[i+1];
    }
    --(*pqr);
    return res;
}

void bfs(Graph *adj_mat) {
    int vertex, *visited, *queue, qr = -1;

    // Accept user input
    printf("enter source vertex");
    scanf("%d", vertex);


    // Out of bounds
    if(vertex < 0 || vertex >= adj_mat->n) {
        printf("vertexc not in graph");
        return;
    }

    // Initialise visited list and q 
    visited = (int*) calloc(adj_mat->n, sizeof(int));
    queue = (int*) calloc(adj_mat->n, sizeof(int));

    // Loop
    append(queue, vertex, &qr);
    visited[vertex] = 1;

    // while q is not empty
    while (qr != -1) {
        vertex= delete(queue, &qr);
        printf("%d ", vertex);
        for (int i=0; i<adj_mat->n; i++) {
            if (adj_mat->adj[vertex][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                append(queue, i , &qr);
            }
        }
    }

    printf("\n");
    // Free memory used by visited and queue
    free(visited);
    free(queue);
}

// for adjacency list
// Just the while  loop will be different (and change all adj_mat->n to n)
while (qr != -1) {
    vertex= delete(queeue, &qr);
    printf("%d ", vertex);

    Node *traverse = adj_list[vertex];

    while (traverse) {
        if (visited[traverse->data] == 0) {
            visited[traverse->data] = 1;
            append(queue, traverse->data, &qr);
        }
        traverse = traverse->next;
    }
}

// function to print the dfs_path
void print_path