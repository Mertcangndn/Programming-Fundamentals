#ifndef HEADER_H
#define HEADER_H

//Node Struct
typedef struct Node{
    char *name;
    struct Node* next;
    struct Node* prev;
}Node;

//Fonksiyon Header'leri
void addSongToEnd(Node** head, char* isim);
void removeSong(Node** head, char* isim);
void playNext(Node* head);
void playPrevious(Node* head);
void menu(Node** head);

#endif