#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void menu(Node** head){
    int select;
    while(1){
        //Menüyü listeleme
        printf("\n\n\n------------------------\n");
        printf("[1] Kelime Eklen\n");
        printf("[2] Geri Al\n");
        printf("[3] Yaziyi Goster");
        printf("\n------------------------\n\n\n");
        printf("Secimin: ");
        scanf("%d",&select);

        switch(select){
            case 1:
                addWord(head);
                break;
            case 2:
                undoWord(head);
                break;
            case 3:
                showText(*head);
                break;
            default:
                printf("\n\n\n------------------------\n");
                printf("Yanlis Girdi, Lutfen Tekrar Deneyin!");
                printf("\n------------------------\n\n\n");
                break;
        }
    }
}