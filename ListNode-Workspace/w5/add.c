#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void add(Node** head){

    char name[50];


    printf("\n\n\n------------------------\n");
    printf("Lutfen Hastanin Adini Giriniz:");
    scanf("%s",name);
    printf("------------------------\n\n\n");


    //Yeni Node oluşturma
    Node* newNode = malloc(sizeof(Node));
    newNode->ID=idGenerator(*head);
    strcpy(newNode->name,name);
    strcpy(newNode->current,"Bekliyor");
    newNode->next=NULL;

    if(*head==NULL){    //Hiç node yoksa
        *head = newNode;
        printf("\n\n\n------------------------\n");
        printf("HASTA KAYDEDİLDİ");
        printf("\n------------------------\n\n\n");
        return;
    }

    Node* tempNode = *head;
    while(1){
        if(tempNode->next==NULL){
            tempNode->next=newNode;
            printf("\n\n\n------------------------\n");
            printf("HASTA KAYDEDİLDİ");
            printf("\n------------------------\n\n\n");
            return;
        }
        tempNode=tempNode->next;
    }
}