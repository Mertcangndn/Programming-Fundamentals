#include "header.h"

int main(void){
    int number;
    //loadingScreen();    //test aşamasında kolayca çalıştırıp denemek için yorum satırına alınabilir.
    menu();


    // ------ DENEME KODU -------
    File* root = createFile("C:",1);
    addFile(root, "Odevler", 1);       
    addFile(root, "Oyunlar", 1);       
    addFile(root, "notlar.txt", 0);    
    // addFile("Odevler", "Animeler", 1); //BUNLAR SONRA FİND FONKSİYONUYLA BİRLİKTE KULLANILACAK
    // addFile("Animeler", "highschoolDxD.mp4", 0);

    // listDirectory(root);

    listAllDirectory(root);
    // --------------------------
    
    printf("\n");system("pause");return 0;//cmd'de iş bittikten sonra pencere hemen kapanması diye pause kodu.
}