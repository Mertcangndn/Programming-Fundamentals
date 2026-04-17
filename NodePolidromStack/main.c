#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;


Node* createNode(int value){
    Node* newNode = malloc(sizeof(Node));
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}

int pop(Node** head){
    if (*head == NULL) {
        printf("HATA: Boş stack'ten pop yapılamaz!\n");
        return -1; // Hata
    }
    Node* tempNode = *head;
    int value = tempNode->value;
    (*head)=(*head)->next;
    free(tempNode);
    return value;
}

Node* push(Node* head,Node* newNode){
    newNode->next=head;
    return newNode;
}

void printStack(Node* head){
    if(head==NULL)return;

    printf("%d->",head->value);
    printStack(head->next);
}

int equals(int number, Node** head){

    while(number!=0){
        if(number%10!=pop(head)){
            return 0;
        }
        number = (int)(number/10);
    }
    return 1;
}


int main(void){
    int number;
    printf("Bir sayi giriniz: ");
    scanf("%d",&number);
    //BURAYA GİRİLEN SAYIYI KONTROL ETMEK İÇİN BİR KOD BLOĞU EKLENEBİLİR.
    int tempNumber=number;

    Node* stackHead = NULL;

    //Değerleri stack'e atma
    while(tempNumber!=0){
        Node* newNode = createNode(tempNumber%10);
        stackHead = push(stackHead,newNode);
        tempNumber=tempNumber/10;
    }

    printStack(stackHead);

    if(equals(number,&stackHead)){
        printf("\n\nSAYI POLIDROMDUR.");
    }else{
        printf("\n\nSAYI POLIDROM DEGILDIR.");
    }
    
    return 0;
}