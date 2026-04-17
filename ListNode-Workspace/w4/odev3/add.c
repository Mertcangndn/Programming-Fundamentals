#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void enqueuePrintJob(Queue* q, char* dosyaAdi){

    PrintJob* newJob = malloc(sizeof(PrintJob));
    strcpy(newJob->fileName,dosyaAdi);
    newJob->next=NULL;

    if(q->rear==NULL){  //boşsa
        q->rear=newJob;
        q->front=newJob;

        printf("\n\nDosya Siraya Eklendi: %s\n\n",dosyaAdi);

    }else{  //zaten içinde bir şeyler varsa ve ekleme yapılıyorsa
        q->rear->next=newJob;
        q->rear=newJob;
        printf("\n\nDosya Siraya Eklendi: %s\n\n",dosyaAdi);
    }
}