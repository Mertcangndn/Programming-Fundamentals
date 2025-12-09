#include "header.h"

//Windows için Evrensel Renk Fonksiyonu
//Renk Kodları:
// Siyah             =   0
// Koyu Mavi         =   1
// Koyu Yeşil        =   2
// Koyu Turkuaz      =   3
// Koyu Kırmızı      =   4
// Mor               =   5
// Koyu Sarı (Toprak)=   6
// Beyaz (Default)   =   7
// Gri               =   8
// Açık Mavi         =   9
// Açık Yeşil        =   10
// Turkuaz           =   11
// Açık Kırmızı      =   12
// Pembe             =   13
// Sarı              =   14
// Parlak Beyaz      =   15

void color(int code) {
    // 7 = Beyaz (Normal), 10 = Açık Yeşil, 12 = Açık Kırmızı, 14 = Sarı
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}