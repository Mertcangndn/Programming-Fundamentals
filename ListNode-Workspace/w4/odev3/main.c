#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(void){

    PrintJob* head=NULL;

    Queue queue;
    queue.front=head;
    queue.rear=head;

    char fileName[50];

    //menu
    int select;
    while(1){
        //Menüyü listeleme
        printf("\n\n\n------------------------\n");
        printf("[1] Yeni Dosya Ekle\n");
        printf("[2] Yazdir\n");
        printf("[3] Kuyrugu Goster");
        printf("\n------------------------\n\n\n");
        printf("Secimin: ");
        scanf("%d",&select);

        switch(select){
            case 1:
                printf("\nYuklemek Istediginiz Dosyanin Ismini Girin: ");
                scanf("%s",fileName);

                enqueuePrintJob(&queue, fileName);
                break;
            case 2:
                processNextJob(&queue);
                break;
            case 3:
                showQueue(queue);
                break;
            default:
                printf("\n\n\n------------------------\n");
                printf("Yanlis Girdi, Lutfen Tekrar Deneyin!");
                printf("\n------------------------\n\n\n");
                break;
        }
    }

    return 0;
}