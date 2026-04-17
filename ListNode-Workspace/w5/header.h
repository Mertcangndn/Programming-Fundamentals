#ifndef HEADER_H
#define HEADER_H

//Node Struct
typedef struct Node {
    int ID;
    char name[50];
    char current[15];
    struct Node* next;
}Node;

//Fonksiyon Header'leri
int idGenerator(Node* head);//Hastalar için ID oluşturma fonksiyonu
void add(Node** head);      //Yeni hasta girişi yapma fonksiyonu
void enter(Node** head);    //Hastayı muayeneye sokma fonksiyonu
void ext(Node** head);     //Hastayı muayeneden çıkartma fonksiyonu
void printList(Node* head); //Hasta listesini yazdırma fonksiyonu

#endif