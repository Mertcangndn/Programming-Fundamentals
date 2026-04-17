#ifndef HEADER_H
#define HEADER_H

//Node Struct
typedef struct Node{
    char word[20];
    struct Node* next;
}Node;

//Fonksiyon Header'leri
void menu(Node** head);
void addWord(Node** head);
void undoWord(Node** head);
void showText(Node* head);

#endif