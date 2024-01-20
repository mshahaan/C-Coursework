#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node *leftChild;
    struct node *rightChild;

}node;

int insert(node *root, int x){

    if(root == NULL){
        node *newNode = (node*) malloc(sizeof(node));
        root = newNode;
        return 1;
    }

    node *newNode = (node*) malloc(sizeof(node));

    newNode->data = x; newNode->leftChild = NULL; newNode->rightChild = NULL;

    node *ptr = root; node *prev = NULL;

    while(ptr != NULL){
        prev = ptr;
        if(newNode->data > ptr->data){
            ptr = ptr->rightChild;
        }
        else if(newNode->data < ptr->data){
            ptr = ptr->leftChild;
        }
        else return 0;
    }

    if(newNode->data > prev->data){
        prev->rightChild = newNode;
        return 1;
    }
    else if(newNode->data < prev->data){
        prev->leftChild = newNode;
        return 1;
    }
    else return 0;

}

int search_node(node *root, int x){

    if(root == NULL) return 0;

    node *ptr = (node*) malloc(sizeof(node));

    ptr = root;

    while(ptr != NULL){

        if(ptr->data == x) return 1;
        if(ptr->data > x){
            ptr = ptr->leftChild;
            continue;
        }
        if(ptr->data < x){
            ptr = ptr->rightChild;
            continue;
        }
    }

    return 0;

}

void printTree(node *root){

    if(root->leftChild == NULL && root->rightChild == NULL) printf("%d)\n", root->data);

}

int delete_node(node *root, int x){

    if(root == NULL) return 0;

    node *ptr = root; node *prev = NULL; node *target = malloc(sizeof(node));

    while(ptr != NULL){

        if(ptr->data == x){ target = ptr; break; }
        if(ptr->data > x){
            prev = ptr;
            ptr = ptr->leftChild;
        }
        if(ptr->data < x){
            prev = ptr;
            ptr = ptr->rightChild;
        }
    }

    if(ptr == NULL) return 0;

    if(target->leftChild == NULL && target->rightChild == NULL){
        if(prev->data < x){ prev->rightChild = NULL; free(target); }
        else{ prev->leftChild = NULL; free(target);}
        return 1;
    }
    else if(target->leftChild == NULL){
        target->data = target->rightChild->data;
        target->rightChild = target->rightChild->rightChild;
        target->leftChild = target->rightChild->leftChild;
        free(ptr);
        return 1;
    }
    else if(target->rightChild == NULL){
        target->data = target->leftChild->data;
        target->rightChild = target->leftChild->rightChild;
        target->leftChild = target->leftChild->leftChild;
        free(ptr);
        return 1;
    }
    else{
        ptr = target->rightChild;
        prev = NULL;

        while(ptr->leftChild != NULL){
            prev = ptr;
            ptr = ptr->leftChild;
        }

        target->data = ptr->data;

        if(prev == NULL) return delete_node(target->rightChild, target->rightChild->data);
        else return delete_node(prev->leftChild, prev->leftChild->data);
    }

    return 0;

}


int main(){

    char op;

    int num; int firstOperation = 1;

    node *root = (node*) malloc(sizeof(node));

    root->data = 0; root->leftChild = NULL; root->rightChild = NULL;

    while(scanf("%c %d", &op, &num) != EOF){

        getchar();

        if(op == 'i'){

            if(firstOperation){
                firstOperation = 0;
                root->data = num;
                printf("inserted\n");
            }
            else{
                int x = insert(root, num);
                if(x == 1) printf("inserted\n");
                else printf("not inserted\n");
            }

        }
        else if(op == 'd'){

            if(firstOperation) printf("absent\n");
            else{
                int x = delete_node(root, num);
                if(x == 1) printf("deleted\n");
                else printf("absent\n");
            }

        }
        else if(op == 'p'){

            if(firstOperation) printf("\n");
            else{
                printf("(");
                printTree(root);
            }

        }
        else if(op == 's'){

            if(firstOperation){
                firstOperation = 0;
                printf("absent\n");
            }
            else{
                int x = search_node(root, num);
                if(x == 1) printf("present\n");
                else printf("absent\n");
            }

        }
        else{

            printf("Input Error.\nTerminating...");

            return 0;

        }

    }

    return 0;

}
