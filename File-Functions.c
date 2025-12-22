#include "header.h"

// YENİ DOSYA OLUŞTURMA FONKSİYONU
File* createFile(char* name,int isFolder){
    File* newFile = malloc(sizeof(File));

    strcpy(newFile->name,name);
    newFile->isFolder=isFolder;
    newFile->deletedTime = 0;           // 0 = aktif dosya (silinmemiş)
    newFile->originalPath[0] = '\0';    // Başlangıçta boş
    newFile->child=NULL;
    newFile->parent=NULL;
    newFile->sibling=NULL;

    return newFile;
}

// DOSYAYI GRAFA EKLEME
void addFile(File* currentFile, char* name, int isFolder){ //Burası degisebilir sona kucuk bir ekleme(Eray)
    
    File* newFile = createFile(name, isFolder); //Yeni Dosya Oluşturma
    
    newFile->sibling = currentFile->child;  //Yeni oluşturduğumuz dosya kardeş olarak parent'ın ilk çocuğunu gösteriyor.
    currentFile->child = newFile;           //Parent artık ilk çocuk olarak bizim yeni dosyamızı tutuyor.
                                            //Yani, yeni dosya sibling zincirinin ilk elemanı olarak kaynak yapmış oldu.
    newFile->parent = currentFile;          //Geri dönmek gerekirse diye parent node kaydedildi.

}


// ============================================================
// 
// listDirectory() fonksiyonu Volkan Taştemir tarafından güncellendi.
// 
// DEĞİŞİKLİK NEDENİ:
// - Geri dönüşüm kutusunu test ederken dizin yapısını görmemiz gerekiyordu
// - Eski versiyon düz liste halinde gösteriyordu, hiyerarşi anlaşılmıyordu
// - Yeni versiyon ağaç (tree) görünümünde gösteriyor
//
// YAPILAN DEĞİŞİKLİKLER:
// - printTreeSimple() yardımcı fonksiyonu eklendi
// - listDirectory() tamamen yeniden yazıldı
// - Klasörler [köşeli parantez] içinde gösteriliyor
// - Alt klasörler girintili şekilde listeleniyor
//
// ESKİ VERSİYONU GERİ ALMAK İSTERSENİZ:
// Bu bloğu silin ve eski kodunuzu geri koyun.
// ============================================================

// Yardımcı: Ağaç yapısını yazdırır
void printTreeSimple(File* node, char* prefix, int isLast) {
    if (node == NULL) return;
    
    // Mevcut satırı yazdır
    printf("%s", prefix);
    printf("%s", isLast ? "+-- " : "|-- ");
    
    if (node->isFolder) {
        printf("[%s]\n", node->name);
    } else {
        printf("%s\n", node->name);
    }
    
    // Yeni prefix oluştur (child'lar için)
    char newPrefix[500];
    strcpy(newPrefix, prefix);
    strcat(newPrefix, isLast ? "    " : "|   ");
    
    // Eğer klasörse, child'ları yazdır
    if (node->isFolder && node->child != NULL) {
        File* child = node->child;
        while (child != NULL) {
            int childIsLast = (child->sibling == NULL);
            printTreeSimple(child, newPrefix, childIsLast);
            child = child->sibling;
        }
    }
}

void listDirectory(File* currentFile){
    if (currentFile == NULL) {
        printf("(Gecersiz dizin)\n");
        return;
    }
    
    printf("\n");
    printf("=====================================\n");
    printf("          DIZIN YAPISI\n");
    printf("=====================================\n\n");
    
    // Kök dizini yazdır
    printf("[%s]\n", currentFile->name);
    
    // Alt öğeleri yazdır
    if (currentFile->child == NULL) {
        printf("    (bos)\n");
    } else {
        File* child = currentFile->child;
        while (child != NULL) {
            int isLast = (child->sibling == NULL);
            printTreeSimple(child, "", isLast);
            child = child->sibling;
        }
    }
    
    printf("\n=====================================\n");
}

File* changeDirectory(File* currentFile, char* target){ // Burasi degisebilir(Eray)
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

