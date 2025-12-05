#include "header.h"

void menu(void){

    char loadingWheel[]={'/','-','\\','|'};

printf("\033[0;32m"); //Yeşil renk
    printf("\n\n\n");
    printf("    ______ _ __      __  ___                                   __           \n");
    printf("   / ____/(_) /___  /  |/  /___ _____  ____ _____ ____  ____  / /_          \n");
    printf("  / /_   / / / _ \\ / /|_/ / __ `/ __ \\/ __ `/ __ `/ _ \\/ __ \\/ __/      \n");
    printf(" / __/  / / /  __// /  / / /_/ / / / / /_/ / /_/ /  __/ / / / /_            \n");
    printf("/_/    /_/_/\\___//_/  /_/\\__,_/_/ /_/\\__,_/\\__, /\\___/_/ /_/\\__/      \n");
    printf("                                          /____/                            \n");
    printf("               ______  __  __________________  __                              \n");
    printf("              / __/\\ \\/ / / __/_  __/ ____/  |/  /                           \n");
    printf("             _\\ \\   \\  / _\\ \\  / / / __/ / /|_/ /                          \n");
    printf("            /___/   / / /___/ / / / /___/ /  / /                                 \n");
    printf("                   /_/       /_/ /_____/_/  /_/                                  \n");
    printf("\n");
printf("\033[0;31m"); //Kırmızı renk
    printf("                  Mertcan Gundogan\n");
    printf("                   Volkan Tastemir\n");
    printf("                     Eray Bekar\n\n");
printf("\033[0;34m"); //Mavi renk
    printf("                    Yukleniyor...");
    
    //DÖNME EFEKTİ
    for(int i=0;i<15;i++){
        for(int j=0;j<4;j++){
            printf("%c",loadingWheel[j]);
            Sleep(150);
            printf("\b \b");
        }
    }

printf("\033[0m"); //Beyaz renk (default)
    system("cls");  //Yüklenme ekranını silme

}