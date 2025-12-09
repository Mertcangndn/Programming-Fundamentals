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

// Fonksiyon Prototiplerini (İmzalarını Buraya Yazalım)
// exp: void create_file(const char *filename); gibi gibi
void menu(void);   //gerçek komut satırı menüsü
void loadingScreen(void); //loding screen için ayrı fonksiyon (test açamasında kolayca kaldırabilmek için)
void color(int code);   //CMD Üzerindeki yazıları değiştirmek için kullanılan fonksiyon. Renk kodlarını görmek için "../color.c" altına bakılabilir.

// 1. Dosya İşlemleri
//...
// 2. Klasör İşlemleri
//...
//
//
#endif