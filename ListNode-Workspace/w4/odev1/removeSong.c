#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeSong(Node** head, char* isim){
    //NULL Kontrolü
    if(*head==NULL){
        printf("\n\n\n------------------------\n");
        printf("LISTE BOS!!!");
        printf("\n------------------------\n\n\n");
        return;
    }

    //Geçici Node Oluşturma
    Node* tempNode = *head;
    Node* prevTempNode = NULL;
    
    while(tempNode!=NULL){
        if(strcmp(tempNode->name,isim)==0){   //Eşleşiyorsa
            printf("eşleşme bulundu");

            if(tempNode->next==NULL && tempNode->prev==NULL){  //Tek Şarkı Varsa

                *head==NULL;

                printf("\n\n\n------------------------\n");
                printf("MUZIK SILINDI");
                printf("\n------------------------\n\n\n");

                return;
            }else if(tempNode->prev==NULL){ //İlk şarkı eşleşiyorsa

                *head=tempNode->next;
                (*head)->prev=NULL;
                free(tempNode);

                printf("\n\n\n------------------------\n");
                printf("MUZIK SILINDI");
                printf("\n------------------------\n\n\n");

                return;
            }else if(tempNode->next==NULL){ //Sondaki şarkıysa
                prevTempNode->next=NULL;
                free(tempNode);

                printf("\n\n\n------------------------\n");
                printf("MUZIK SILINDI");
                printf("\n------------------------\n\n\n");
                
                return;
            }else{  //Ortadaki şarkıysa
                prevTempNode->next=tempNode->next;
                (tempNode->next)->prev=prevTempNode;
                free(tempNode);

                printf("\n\n\n------------------------\n");
                printf("MUZIK SILINDI");
                printf("\n------------------------\n\n\n");

                return;
            }

        }else{
            //İleri gitme işi
            prevTempNode=tempNode;
            tempNode=tempNode->next;

            if(tempNode==NULL){ //Şarkı bulunamadıysa
                printf("\n\n\n------------------------\n");
                printf("MUZIK BULUNAMADI!!!!");
                printf("\n------------------------\n\n\n");
            }
        }
    }
    

}