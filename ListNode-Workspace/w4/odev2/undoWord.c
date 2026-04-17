#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void undoWord(Node** head){
    if(*head==NULL){    //Kelime yoksa
        return;
    }else if((*head)->next==NULL){   //Tek kelime kaldıysa
        *head=NULL;
    }else{
        Node* tempNode = *head;
        *head=(*head)->next;
        free(tempNode);
    }
}