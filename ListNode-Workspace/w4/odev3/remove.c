#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void processNextJob(Queue* q){

    if(q->front==NULL){ //Boşsa
        return;
    }

    PrintJob* tempJob = q->front;
    
    if(q->front==q->rear){    //tek eleman varsa
        q->rear=NULL;
        q->front=NULL;
        free(tempJob);

        printf("\n\nYazdirma Basarili\n\n");
    }else{  //Başka elemanlar varsa
        q->front = q->front->next;
        free(tempJob);
        printf("\n\nYazdirma Basarili\n\n");
    }

}