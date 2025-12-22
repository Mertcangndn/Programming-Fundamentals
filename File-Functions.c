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


 HashNode* hashTable[TABLE_SIZE];
// Hash Fonksiyonu (Djb2)
unsigned int hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash % TABLE_SIZE;
}

// Hash Tablosuna Ekleme Yardımcı Fonksiyonu
void addToHashTable(char* name, File* filePtr) {
    unsigned int index = hash(name);
    
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->name, name);
    newNode->filePtr = filePtr;
    newNode->next = hashTable[index]; // Listenin başına ekle (chaining)
    
    hashTable[index] = newNode;

    
}

// DOSYAYI GRAFA EKLEME
void addFile(File* currentFile, char* name, int isFolder){ //Burası degisebilir sona kucuk bir ekleme(Eray)
    
    File* newFile = createFile(name, isFolder); //Yeni Dosya Oluşturma
    
    newFile->sibling = currentFile->child;  //Yeni oluşturduğumuz dosya kardeş olarak parent'ın ilk çocuğunu gösteriyor.
    currentFile->child = newFile;           //Parent artık ilk çocuk olarak bizim yeni dosyamızı tutuyor.
                                            //Yani, yeni dosya sibling zincirinin ilk elemanı olarak kaynak yapmış oldu.
    newFile->parent = currentFile;          //Geri dönmek gerekirse diye parent node kaydedildi.

    // 2. YENİ KISIM: Dosyayı Hash Tablosuna Kaydet
    // Artık aramalarda ağacı gezmek yerine buraya bakacağız.
    addToHashTable(name, newFile);
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

File* changeDirectory(File* currentFile, char* target){
    
    // 1. Hedef ismin hash değerini bul
    unsigned int index = hash(target);
    
    // 2. O indeksteki listeyi getir
    HashNode* temp = hashTable[index];

    // 3. Hash zincirinde (Linked List) arama yap
    while(temp != NULL){
        
        // İsim eşleşiyor mu?
        if(strcmp(temp->name, target) == 0){
            
            // KRİTİK KONTROL:
            // Hash tablosu tüm sistemdeki "odev" klasörlerini getirir.
            // Biz sadece ŞU ANKİ klasörün (currentFile) altındakini istiyoruz.
            if(temp->filePtr->parent == currentFile){
                
                // Bulunan hedef klasör mü? (Dosyaya cd yapılamaz)
                if(temp->filePtr->isFolder){
                    return temp->filePtr; // Hedef klasörü döndür
                } else {
                    // Bulundu ama bir dosya, klasör değil.
                    // İstersen burada NULL döndürebilir veya uyarı verebilirsin.
                    return NULL; 
                }
            }
        }
        temp = temp->next; // Zincirdeki sonraki elemana bak
    }

    // 4. Eğer döngü biterse dosya bu dizinde yok demektir.
    return NULL;
}

