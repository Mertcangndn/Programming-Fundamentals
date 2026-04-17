#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

void printfNodes(Node* head){
    if(head==NULL){
        return;
    }

    printf("%d -> ",head->value);   //İleri yazdırma

    printfNodes(head->next);    //Recursive Stack

    printf("%d -> ",head->value);   //Geri yazdırma
    
}

int main(void){

    Node* head = malloc(sizeof(Node));
    head->value=0;
    head->next=NULL;
    Node* tempNode = head;

    //Node oluşturma
    for(int i=0 ; i<10 ; i++){
        Node* newNode = malloc(sizeof(Node));
        newNode->value=i+1;
        newNode->next=NULL;
        tempNode->next=newNode;
        tempNode=newNode;
    }

    printfNodes(head);

    return 0;
}