#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addSongToEnd(Node** head, char* isim){
    //Yeni şarkı tanımlama şeysi
    Node* newNode=malloc(sizeof(Node));
    newNode->name=malloc(strlen(isim) + 1);
    strcpy(newNode->name,isim);
    newNode->next=NULL;
    newNode->prev=NULL;

    //NULL Kontrolü
    if(*head==NULL){
        *head=newNode;
        printf("\n\n\n------------------------\n");
        printf("YENI MUZIK EKLENDI: %s",isim);
        printf("\n------------------------\n\n\n");
        return;
    }

    //Geçici Node Oluşturma
    Node* tempNode = *head;

    //Sona gitme
    while(tempNode->next!=NULL){
        tempNode=tempNode->next;
    }

    //Yerleştirme işlemi
    tempNode->next=newNode;
    newNode->prev=tempNode;
    printf("\n\n\n------------------------\n");
    printf("YENI MUZIK EKLENDI: %s",isim);
    printf("\n------------------------\n\n\n");

}