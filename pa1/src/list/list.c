#include <stdlib.h>
#include <stdio.h>

int isEmpty = 1;

typedef struct node {

    int data;

    struct node *next;

}node;

void insert_node(int x, node **list){

    node *newNode = malloc(sizeof(node));

    node *ptr = *list;

    newNode->data = x; newNode->next = NULL;

    while(ptr != NULL){

        if(newNode->data > ptr->data){
            if(ptr->next == NULL){ ptr->next = newNode; break; }
            else if(newNode->data < ptr->next->data){
                newNode->next = ptr->next;
                ptr->next = newNode;
                break;
            }
        }

        if(newNode->data < ptr->data){
            newNode->next = ptr;
            *list = newNode;
            break;
        }

        if(newNode->data == ptr->data){ free(newNode); break; }

        ptr = ptr->next;

    }

}

void delete_node(int x, node **p){

    node *ptr = *p;

    if(ptr->data == x){
        *p = ptr->next;
        return;
    }

    while(ptr->next != NULL){

        if(ptr->next->data == x){
            ptr->next = ptr->next->next;
            break;
        }

        if(ptr->next->next == NULL){
            return;
        }

        ptr = ptr->next;

    }

}

int getSize(node **p){

    int size = 0;

    node * ptr = *p;

    if(ptr->next == NULL) return 1;
    if(ptr == NULL) return 0;

    while(ptr != NULL){
        size++;
        ptr = ptr->next;
    }

    return size;

}

void printList(int size, node **p){

    if(size == 0){
        printf("0 :\n");
        return;
    }

    printf("%d : ", size);

    node * ptr = *p;

    while(ptr != NULL){
        if(ptr->next == NULL){
            printf("%d", ptr->data);
        }
        else{
            printf("%d ", ptr->data);
        }

        ptr = ptr->next;
    }

    printf("\n");

}

int main(){

    char op;

    int num; int firstIteration = 1;

    node *list = (node*) malloc(sizeof(node));

    list->data = -1; list->next = NULL;

    while(1){

        int x = scanf("%c %d", &op, &num);

        if (x == EOF) break;

        getchar();

        if (op == 'i'){
            if(firstIteration == 1){
                if(num == -1){
                    printList(1, &list);
                }
                else{
                    insert_node(num, &list);
                    delete_node(-1, &list);
                    firstIteration = 0;
                    printList(1, &list);
                }
                isEmpty = 0;
            }
            else{
                if(isEmpty){
                    list = (node*) malloc(sizeof(node));
                    list->data = -1; list->next = NULL;
                    insert_node(num, &list);
                    delete_node(-1, &list);
                    printList(1, &list);
                    isEmpty = 0;
                }
                else{
                    insert_node(num, &list);
                    int y = getSize(&list);
                    printList(y, &list);
                }
            }
        }
        else if (op == 'd'){
            if(firstIteration){
                printf("0 :\n");
            }
            else if(isEmpty){
                printf("0 :\n");
            }
            else if(getSize(&list) == 1 && num == list->data){
                printf("0 :\n");
                isEmpty = 1;
            }
            else{
                delete_node(num, &list);
                int y = getSize(&list);
                printList(y,  &list);
            }
        }
        else printf("Invalid Operation.");

    }

    return 0;

}
