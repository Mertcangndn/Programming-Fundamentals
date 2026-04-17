#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void playNext(Node* head){
    if(head->next!=NULL)
        printf("Caliniyor: %s",(head->next)->name);
}

void playPrevious(Node* head){
    if(head->prev!=NULL)
        printf("Caliniyor: %s",(head->prev)->name);
}