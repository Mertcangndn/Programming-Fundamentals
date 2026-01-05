#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

//Kullanacağımız Kütüphaneler (Başka kütüphane kullanırsak buraya ekleyelim arkadaşlar.)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //CLI Menü için kütüphane
#include <windows.h>
#include <time.h>   //Zaman işlemleri için (Geri Dönüşüm Kutusu)
//==========================================================================================================================================



//Sabitler (Buffer boyutları vs. buraya yazalım)
#define MAX_FILENAME 100
#define MAX_PATH_LENGTH 260         //Dosya yolu maksimum uzunluğu
#define RECYCLE_TIMEOUT 604800      //7 gün (saniye cinsinden) - Otomatik temizlik süresi
#define TABLE_SIZE 1009 // Hash tablosu boyutu
//==========================================================================================================================================


//Struct'lar
//Projenin klasör ve dosya yapısı (Aslında node)
typedef struct File{
    char name[MAX_FILENAME];    //Klasör veya Dosya adı

    int isFolder;   // 1:Klasör 0:Dosya
    
    time_t deletedTime;
    char originalPath[MAX_PATH_LENGTH];
    
    struct File* parent;    //Önceki dosyayı tutar.
    struct File* sibling;   //Aynı seviyedeki dosyaların ilkini tutar (birbirine zincir misali bağlanırlar).
    struct File* child;     //Klasörün altındaki diğer dosyalardan ilkini tutar, o da diğerini tutar...

}File;

typedef struct RecycleBin{
    File* root;
    File* tail;
    int itemCount;
    int timeoutSeconds;
}RecycleBin;
//==========================================================================================================================================

// Harici Hash Düğümü (File struct'ına dokunmamak için)
typedef struct HashNode {
    char name[MAX_FILENAME];
    File* filePtr;          // Asıl File düğümüne işaret eder
    struct HashNode* next;  // Çakışma (collision) olursa zincirleme için
} HashNode;




// Fonksiyon Prototiplerini (İmzalarını Buraya Yazalım)
// 1. Genel
void menu(void);   // gerçek komut satırı menüsü
void loadingScreen(void); //loading screen için ayrı fonksiyon (test açamasında kolayca kaldırabilmek için)
void color(int code);   //CMD Üzerindeki yazıların rengini değiştirmek için kullanılan fonksiyon. Renk kodlarını görmek için "../color.c" altına bakılabilir.
void defaultPath(File* root); //Proje açıldığında halihazırda bir dizin olmasını sağlar
void syncTreeToHash(File* node); //Ağaçtaki tüm dosyaları gezip Hash Tablosuna ekleyen fonksiton

// 2. Dosya İşlemleri
File* createFile(char* name,int isFolder);  //Node oluşturma (addFile içinde kendinden çalışıyor.)
void addFile(File* currentFile, char* name, int isFolder); //Dosyayı grafa ekleme
void listDirectory(File* currentFile);   // [DEĞİŞTİ - Volkan] Ağaç görünümü eklendi, File-Functions.c'deki yorumu okuyun
void printTreeSimple(File* node, char* prefix, int isLast); //Ağaç yazdırmakta kullanılan fonksiyon
File* changeDirectory(File* currentFile, char* target); //Mevcut dizin altında istenen dosyayı arayıp bulup yerini döndürür.
void directoryPrinter(File* currentFile); //Mevcut dizinin yolunu yazdırmaya yarayan fonksiyon (direkt çıktı verir)
File* findDirectory(char* target); //Hash table ile rastgele bir yerdeki dosya bulunabilir [EKLEME - MERTCAN]
void printTreeColored(File* node, char* prefix, int isLast, File* target); //renkli şekilde dizin yazdıran fonksiyon (printSimpleTree() fonksiyonunun modifiye edilmiş halidir.) [EKLEME - MERTCAN]


// 3. Geri Dönüşüm Kutusu İşlemleri
int countChildren(File* file);
RecycleBin* initRecycleBin(int timeoutSeconds);
void buildPath(File* file, char* buffer);
int deleteFile(File* parent, char* fileName, RecycleBin* bin);
void clearPath(File* file);
int restoreFile(RecycleBin* bin, char* fileName, File* root);
void autoCleanRecycleBin(RecycleBin* bin);
void freeFile(File* file);
void listRecycleBin(RecycleBin* bin);
//==========================================================================================================================================
unsigned int hash(char *str);
void addToHashTable(char* name, File* filePtr);

#endif