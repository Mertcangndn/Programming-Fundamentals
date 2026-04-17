#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void printList(Node* head){
    printf("\n\n\n------------------------\n");
    while(head!=NULL){
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n",head->ID,head->name,head->current);
        head=head->next;
    }
    printf("\n------------------------\n\n\n");
}