#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void showQueue(Queue q){
    PrintJob* tempJob = q.front;

    printf("\n\n\n------------------------\n");
    for(int i=1 ; tempJob!=NULL ; i++){
        printf("[%d] %s\n",i,tempJob->fileName);
        tempJob=tempJob->next;
    }
    printf("\n------------------------\n\n\n");
}