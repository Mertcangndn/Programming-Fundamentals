#include "header.h"

// YENİ DOSYA OLUŞTURMA FONKSİYONU
File* createFile(char* name,int isFolder){
    File* newFile = malloc(sizeof(File));

    strcpy(newFile->name,name);
    newFile->isFolder=isFolder;
    newFile->child=NULL;
    newFile->parent=NULL;
    newFile->sibling=NULL;

    return newFile;
}

// DOSYAYI GRAFA EKLEME
void addFile(File* currentFile, char* name, int isFolder){
    
    File* newFile = createFile(name, isFolder); //Yeni Dosya Oluşturma
    
    newFile->sibling = currentFile->child;  //Yeni oluşturduğumuz dosya kardeş olarak parent'ın ilk çocuğunu gösteriyor.
    currentFile->child = newFile;           //Parent artık ilk çocuk olarak bizim yeni dosyamızı tutuyor.
                                            //Yani, yeni dosya sibling zincirinin ilk elemanı olarak kaynak yapmış oldu.
    newFile->parent = currentFile;          //Geri dönmek gerekirse diye parent node kaydedildi.

}

// Bulunulan dizinin child dosyalarını listelemekte kullanılır.
void listDirectory(File* currentFile){

    File* tempNode = currentFile->child;
    
    if (tempNode == NULL) {
        printf("(Klasor Bos)\n");
        return;
    }

    printf("\n%s\n  \\", currentFile->name);    //2 boşluklu
    
    while(tempNode!=NULL){
        printf("\n  |");    //2 boşluklu
        if(tempNode->isFolder){
            printf("\n  [Klasor]    %s",tempNode->name);    //2 boşluklu
        }else{
            printf("\n  [Dosya]     %s",tempNode->name);    //2 boşluklu
        }
        tempNode = tempNode->sibling;
    }

    printf("\n\n------------------------------\n");
}

// Bütün ağacı listelemekte kullanılır.
void listAllDirectory(File* root, int* spaceCounter){  // [Yapılacak] Kaç boşluk bırakıldığına dair bir log tutulmalı, ona göre her recursive bittiğinde geri gelinmeli ("\b")
    File* tempNode = root;

    //BASE CASE
    if (tempNode == NULL) {
        printf("\n SON");
        return;
    }

    if(tempNode->isFolder){
            printf("\n[Klasor]    %s",tempNode->name);
    }else{
            printf("\n[Dosya]     %s",tempNode->name);
    }

    if(tempNode->child!=NULL){
        for(int i=0 ; i<spaceCounter ; i++)printf(" "); //Boşluk Bırakıcı
        spaceCounter++;
        printf("\n\\");
        listAllDirectory(tempNode->child,spaceCounter);
    }
    
    if(tempNode->sibling!=NULL){
        for(int i=0 ; i<spaceCounter ; i++)printf(""); //Boşluk Bırakıcı
        spaceCounter--;
        printf("\n|");    //2 boşluklu
        listAllDirectory(tempNode->sibling,spaceCounter);
    }

    
}

// Adı girilen dizini bulmakta da kullanılır.
File* changeDirectory(File* currentFile, char* target){
    File* tempNode = currentFile;

    //Base case
    if(strcmp(tempNode->name,target)){
        return tempNode;
    }

    if(tempNode->child!=NULL){ //Eğer alt klasör varsa alta in
        changeDirectory(tempNode->child,target);
    }
    
    if(tempNode->sibling!=NULL){    //Eğer aynı seviyede başka klasör varsa diğerine geç
        changeDirectory(tempNode->sibling,target);
    }

    return NULL;
}