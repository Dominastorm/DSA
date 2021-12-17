#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node *left, *right;
} Node;

typedef struct tree{
    Node *root;
} Tree;

void init(Tree *pt){
    pt -> root = NULL;
}

void create(Tree *pt)
{
    Node *temp,*p,*q;
    int wish;

    printf("Enter the root info\n");
    pt->root=(Node*)malloc(sizeof(Node));
    scanf("%d",&pt->root->info);

    pt->root->left=NULL;
    pt->root->right=NULL;
    
    do{
        printf("Enter an element\n");
        temp=(Node*)malloc(sizeof(Node));
        scanf("%d",&temp->info);
        temp->left=NULL;
        temp->right=NULL;
        q=NULL;
        p=pt->root;
    
        while(p!=NULL)
        {
            q=p;
            if(temp->info < p->info)
            p=p->left;
            else
            p=p->right;
        }
        if(temp->info < q->info)
            q->left=temp;
        else
            q->right=temp;
        
        printf("Do you wish to add another? 1/0\n");
        scanf("%d",&wish);
        }
    while(wish);
    }
void intr(Node* p){
    if(p!=NULL){
        intr(p->left);
        printf("%d ",p->info);
        intr(p->right);
    }
}
void intrav(Tree *pt){
    intr(pt->root);
}

int main()
{
    Tree tobj;
    create(&tobj);
    intrav(&tobj);
    return 0;
}