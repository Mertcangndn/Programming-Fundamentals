#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void addWord(Node** head){

    char word[20];
    printf("Lutfen eklemek istediğini kelimeyi yazin: ");
    scanf("%s",word);

    Node* newNode = malloc(sizeof(Node));
    strcpy(newNode->word,word);
    newNode->next=NULL;

    if(*head==NULL){
        *head=newNode;
        return;
    }else{
        newNode->next=*head;
        *head=newNode;
        return;
    }
}