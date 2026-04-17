#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int idGenerator(Node* head){
    int i = 1;

    while(head!=NULL){
        head=head->next;
        i++;
    }

    return i;
}