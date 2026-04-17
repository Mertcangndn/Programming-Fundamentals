#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(Node** head){

    //Şarkı gezmek içi geçici node oluşturma
    Node* tempNode=*head;
    //seçimi tutmak için değişken ve diğer değişkenler
    char current[20];
    char isim[20];
    int select;


    //UI
    while(1){

        //Menüyü listeleme
        printf("\n\n\n------------------------\n");
        printf("[1] Sarkilari Listele ve Sec\n");
        printf("[2] Sarki Ekle\n");
        printf("[3] Sarki Sil\n");
        printf("[4] Onceki Sarkiyi Cal\n");
        printf("[5] Sonraki Sarkiyi Cal");
        printf("\n------------------------\n\n\n");
        
        scanf("%d",&select);

        switch(select){
            case 1:
                if((*head)==NULL){
                    printf("------------------------\n");
                    printf("-Hic Sarki Bulunamadi-\n");
                    printf("------------------------\n");
                    break;
                }
                
                //LİSTELEME KISMI
                tempNode = *head;
                printf("\n\n\n------------------------\n");
                for(int i=1 ; tempNode!=NULL ; i++){
                    printf("[%d] %s\n",i,tempNode->name);
                    tempNode=tempNode->next;
                }
                printf("------------------------\n\n\n");
                
                //SEÇİMİ ALMA KISMI
                scanf("%d",&select);
                tempNode = *head;
                printf("------------------------\n");
                for(int i=1 ; i<=select && tempNode!=NULL; i++){
                    if(i==select){
                        printf("Caliniyor: %s",tempNode->name);
                        strcpy(current,tempNode->name);
                    }else{
                        tempNode=tempNode->next;
                    }
                }
                printf("\n------------------------\n\n\n");
                break;
            case 2:
                printf("Eklemek Istediginiz Sarkinin Ismini Giriniz: ");
                scanf("%s",isim);
                addSongToEnd(head,isim);
                tempNode=*head;
                break;
            case 3:
                printf("Sılmek Istediginiz Sarkinin Ismini Giriniz: ");
                scanf("%s",isim);
                removeSong(head,isim);
                tempNode=*head;
                break;
            case 4:
                tempNode = *head;
                while(tempNode!=NULL){
                    if(strcmp(tempNode->name,current)==0){
                        break;
                    }else{
                        tempNode=tempNode->next;
                    }
                }
                if(tempNode!=NULL && tempNode->next!=NULL){
                    playPrevious(tempNode);
                    strcpy(current,(tempNode->next)->name);
                }else{
                    printf("BIR HATA OLUSTU");
                }
                tempNode = *head;
                break;
            case 5:
                tempNode = *head;
                while(tempNode!=NULL){
                    if(strcmp(tempNode->name,current)==0){
                        break;
                    }else{
                        tempNode=tempNode->next;
                    }
                }
                if(tempNode!=NULL && tempNode->next!=NULL){
                    playNext(tempNode);
                    strcpy(current,(tempNode->next)->name);
                }else{
                    printf("BIR HATA OLUSTU");
                }
                tempNode = *head;
                break;
            default:
                printf("Yanlis secim, lutfen tekrar deneyin!");
                break;
        }
    }
    
}