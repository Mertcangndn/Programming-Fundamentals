#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

// Kullanacağımız Kütüphaneler (Başka kütüphane kullanırsak buraya ekleyelim arkadaşlar.)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //CLI Menü için kütüphane
#include <windows.h>
#include <time.h>   // Zaman işlemleri için (Geri Dönüşüm Kutusu)



// Sabitler (Buffer boyutları vs. buraya yazalım)
#define MAX_FILENAME 100
#define MAX_PATH_LENGTH 260         // Dosya yolu maksimum uzunluğu
#define RECYCLE_TIMEOUT 604800      // 7 gün (saniye cinsinden) - Otomatik temizlik süresi



// Struct'lar
// Projenin klasör ve dosya yapısı (Aslında node)
typedef struct File{
    char name[MAX_FILENAME];    //Klasör veya Dosya adı

    int isFolder;   // 1:Klasör 0:Dosya
    
    // Geri Dönüşüm Kutusu için eklenen alanlar
    time_t deletedTime;                     // Silinme zamanı (0 = aktif dosya, silinmemiş)
    char originalPath[MAX_PATH_LENGTH];     // Orijinal konum (geri yükleme için kullanılır)
    
    struct File* parent;    //Önceki dosyayı tutar.
    struct File* sibling;   //Aynı seviyedeki dosyaların ilkini tutar (birbirine zincir misali bağlanırlar).
    struct File* child;     //Klasörün altındaki diğer dosyalardan ilkini tutar, o da diğerini tutar...

}File;

// Geri Dönüşüm Kutusu Graf Yapısı
typedef struct RecycleBin{
    File* root;             // Silinen dosyaların kök düğümü
    int itemCount;          // Geri dönüşüm kutusundaki dosya sayısı
    int timeoutSeconds;     // Otomatik temizlik süresi (saniye)
}RecycleBin;



// Fonksiyon Prototiplerini (İmzalarını Buraya Yazalım)
void menu(void);   // gerçek komut satırı menüsü
void loadingScreen(void); //loading screen için ayrı fonksiyon (test açamasında kolayca kaldırabilmek için)
void color(int code);   //CMD Üzerindeki yazıların rengini değiştirmek için kullanılan fonksiyon. Renk kodlarını görmek için "../color.c" altına bakılabilir.

// 1. Dosya İşlemleri
File* createFile(char* name,int isFolder);  //Node oluşturma (addFile içinde kendinden çalışıyor.)
void addFile(File* currentFile, char* name, int isFolder); //Dosyayı grafa ekleme
void listDirectory(File* currentFile);   // [DEĞİŞTİ - Volkan] Ağaç görünümü eklendi, File-Functions.c'deki yorumu okuyun
void listAllDirectory(File* root, int spaceCounter);  // [DEĞİŞTİ - Volkan] int* -> int olarak düzeltildi, yorumu okuyun
File* changeDirectory(File* currentFile, char* target); //Mevcut dizin altında istenen dosyayı arayıp bulup yerini döndürür.
// 2. Klasör İşlemleri
//...

// 3. Geri Dönüşüm Kutusu İşlemleri
int countChildren(File* file);                                          // Klasör altındaki dosya sayısını hesaplar
RecycleBin* initRecycleBin(int timeoutSeconds);                         // Geri dönüşüm kutusu başlatma
void buildPath(File* file, char* buffer);                               // Dosya yolunu oluşturma (yardımcı fonksiyon)
int deleteFile(File* parent, char* fileName, RecycleBin* bin);          // Pointer kaydırma ile silme
void clearPath(File* file);                                             // POSTFIX algoritması ile yol temizleme
int restoreFile(RecycleBin* bin, char* fileName, File* root);           // Geri yükleme
void autoCleanRecycleBin(RecycleBin* bin);                              // Otomatik temizlik (zaman aşımı)
void freeFile(File* file);                                              // Bellek temizleme (recursive)
void listRecycleBin(RecycleBin* bin);                                   // Geri dönüşüm kutusunu listeleme

#endif