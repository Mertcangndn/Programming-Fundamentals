#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void showText(Node* head){
    if(head==NULL){
        return;
    }

    showText(head->next);

    printf("%s ",head->word);

    return;
}