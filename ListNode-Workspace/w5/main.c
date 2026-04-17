#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(void){
    //Node'u oluşturma
    Node* head = NULL;

    //Menü içinde gerekli olacak değişkenleri tanımlama
    int select;
    
    while(1){
        printf("\n\n\n------------------------\n");
        printf("[1] Yeni Hasta Ekle\n");
        printf("[2] Siradaki Hastayi Muayene Et\n");
        printf("[3] Muayeneyi Bitir\n");
        printf("[4] Kuyrugu Goster");
        printf("\n------------------------\n\n\n");
        printf("Secimin: ");
        scanf("%d",&select);

        switch(select){
            case 1:
                add(&head);
                break;
            case 2:
                enter(&head);
                break;
            case 3:
                ext(&head);
                break;
            case 4:
                printList(head);
                break;
            default:
                printf("\n\n\n------------------------\n");
                printf("Hatali Secim, Tekrar Deneyin!");
                printf("\n------------------------\n\n\n");
        }
    }

    return 0;
}