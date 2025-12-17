#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

// Kullanacağımız Kütüphaneler (Başka kütüphane kullanırsak buraya ekleyelim arkadaşlar.)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //CLI Menü için kütüphane
#include <windows.h>



// Sabitler (Buffer boyutları vs. buraya yazalım)
#define MAX_FILENAME 100



// Struct'lar
// Projenin klasör ve dosya yapısı (Aslında node)
typedef struct File{
    char name[MAX_FILENAME];    //Klasör veya Dosya adı

    int isFolder;   // 1:Klasör 0:Dosya
    
    struct File* parent;    //Önceki dosyayı tutar.
    struct File* sibling;   //Aynı seviyedeki dosyaların ilkini tutar (birbirine zincir misali bağlanırlar).
    struct File* child;     //Klasörün altındaki diğer dosyalardan ilkini tutar, o da diğerini tutar...

}File;



// Fonksiyon Prototiplerini (İmzalarını Buraya Yazalım)
void menu(void);   // gerçek komut satırı menüsü
void loadingScreen(void); //loading screen için ayrı fonksiyon (test açamasında kolayca kaldırabilmek için)
void color(int code);   //CMD Üzerindeki yazıların rengini değiştirmek için kullanılan fonksiyon. Renk kodlarını görmek için "../color.c" altına bakılabilir.

// 1. Dosya İşlemleri
File* createFile(char* name,int isFolder);  //Node oluşturma (addFile içinde kendinden çalışıyor.)
void addFile(File* currentFile, char* name, int isFolder); //Dosyayı grafa ekleme
void listDirectory(File* currentFile);   //Bulunulan herdeki dosyaları yazdırma (düz ls)
void listAllDirectory(File* root);  //Bütün grafı yazdırma fonksiyonu (ls -a gibi bir kodla çalışabilir.)
// 2. Klasör İşlemleri
//...

#endif