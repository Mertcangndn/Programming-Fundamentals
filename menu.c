#include "header.h"

void menu(void){
    //printf("FileManagementSystem\\admin> "); //her komutun başındaki prompt (çok uğraştırırsa kaldırabiliriz.) KOMUTLU SİSTEM İÇİN GEÇERLİ

    int choice;
    char fileName[MAX_FILENAME];
    
    File* root = createFile("C:",1);
    defaultPath(root);

    //Geri dönüşüm kutusunu başlat (TEST için 30 saniye timeout)
    RecycleBin* bin = initRecycleBin(30);

    File* currentFile = root;   //Mevcutta bulunulan dizini tutan node

    //Asıl menü kısmı
    while(1) {
        // Otomatik temizlik - her döngüde sessizce kontrol et
        autoCleanRecycleBin(bin);
        
        printf("\n\n========= Dosya Yonetim Sistemi =========\n");
        color(4);
        printf("Current Folder: ");directoryPrinter(currentFile);
        color(7);
        printf("\n============================================\n");
        printf("1. Mevcut Altdizini Goruntule\n");
        printf("2. Dosya veya Klasor Olustur\n");
        printf("3. Dosya veya Klasor Sil\n");
        printf("4. Dizin Degistir\n");
        printf("5. Geri Donusum Kutusunu Listele\n");
        printf("6. Dosyayi Geri Yukle\n");
        printf("7. Dosya veya Klasor Bul\n");
        printf("8. Cikis\n");
        printf("============================================\n");
        printf("Seciminiz: ");
        
        // Girdi doğrulama - geçersiz girişleri yakala
        if (scanf("%d", &choice) != 1) {
            // Geçersiz girdi (sayı değil), buffer'ı temizle
            while (getchar() != '\n');  // Buffer'daki tüm karakterleri temizle
            choice = -1;  // Geçersiz seçim olarak işaretle
        } else {
            getchar(); // Sadece newline karakterini temizle
        }

        switch(choice) {
            case 1:
                system("cls");
                printf("\n--- Mevcut Dizin ---\n");
                listDirectory(currentFile);
                printf("\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                //system("pause");  //bu daha iyi ama türkçe olmadığı için manuel bir kod yazdım.
                system("cls");
                break;
            
            case 2:
                system("cls");
                printf("\n--- Dosya ve Klasor Olusturucu ---\n");
                printf("\nDosya Ismi Giriniz: ");
                scanf("%s",fileName);

                if (strrchr(fileName, '.') != NULL) {   //isminde nokta varsa (code.py) dosya olarak, yoksa klasör olarak oluşturuyor.
                    addFile(currentFile,fileName,0);
                } else {
                    addFile(currentFile,fileName,1);
                }
                printf("Yeni Dosya Eklendi: ");directoryPrinter(findDirectory(fileName));
                printf("\n\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                system("cls");
                break;
                
            case 3:
                system("cls");
                printf("\n--- Dosya ve Klasor Silici ---\n");
                printf("\nSilinecek dosya adi: ");
                scanf("%s", fileName);
                deleteFile(root, fileName, bin);
                if(strcmp(fileName, currentFile->name)==0){
                    currentFile=root;
                    printf("\n[UYARI] Bulundugunuz klasoru sildiniz! Kok dizine donulecek.\n");
                }
                printf("\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                system("cls");
                break;
            
            case 4:
                system("cls");
                printf("\n--- Dizin Degistirici ---\n");
                printf("\nGitmek Istediginiz Klasorun Ismini Giriniz: ");
                scanf("%s",fileName);

                if(strcmp(fileName, "..") == 0){
                    if(currentFile->parent!=NULL){
                        currentFile=currentFile->parent;
                        printf("\n\n[Bilgi] Dizin Degistirildi, Mevcut Dizin: ");directoryPrinter(currentFile);printf("\n\n");
                    }else{
                        printf("\n\n[Bilgi] Ana Dizindesiniz, Daha Uste Cikamassiniz.\n\n");
                    }
                }else if(changeDirectory(root,fileName)!=NULL){
                    currentFile=changeDirectory(root,fileName);
                    printf("\n\n[Bilgi] Dizin Degistirildi, Mevcut Dizin: ");directoryPrinter(currentFile);printf("\n\n");
                }else{
                    printf("\n\nGirilen Isimde Bir Dosya Bulunamadi!\n\n");
                }

                printf("\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                system("cls");
                break;
                
            case 5:
                system("cls");
                listRecycleBin(bin);
                printf("\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                system("cls");
                break;
                
            case 6:
                system("cls");
                printf("\n--- Geri Yukleyici ---\n");
                printf("\nGeri yuklenecek dosya adi: ");
                scanf("%s", fileName);
                restoreFile(bin, fileName, root);
                printf("\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                system("cls");
                break;
            
            case 7:
                system("cls");
                printf("\n--- Dosya Bulucu ---\n");
                printf("\nAradiginiz Dosyanin Adini Giriniz: ");
                scanf("%s", fileName);
                File* foundFile = findDirectory(fileName);

                if(foundFile!=NULL){
                    printTreeColored(root, "", 1, foundFile);
                }
                printf("\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                system("cls");
                break;
                
            case 8:
                printf("\nCikis yapiliyor...\n");
                return;
                
            default:
                printf("\nGecersiz secim!\n");
                printf("\nDevam Etmek icin Herhangi Bir Tusa Basin");
                getch();
                system("cls");
        }
    }
    getch();
}

void defaultPath(File* root) {
    // NOT: addFile fonksiyonu yeni dosyayı listenin EN BAŞINA ekler.
    // Bu yüzden pointer'ı yakalamak için "root->child" dememiz yeterlidir.

    // 1. ODEVLER KLASÖRÜ VE ALTINDAKİLER
    addFile(root, "Odevler", 1);
    File* odevler = root->child; // Odevler node'unu yakaladık

        // 1.1 VeriYapilari
        addFile(odevler, "VeriYapilari", 1);
        File* veriYapilari = odevler->child;

            // 1.1.1 Proje1 ve Dosyaları
            addFile(veriYapilari, "Proje1", 1);
            File* proje1 = veriYapilari->child;
            addFile(proje1, "main.c", 0);
            addFile(proje1, "header.h", 0);
            addFile(proje1, "README.md", 0);

            // 1.1.2 Diğer VeriYapilari Dosyaları
            addFile(veriYapilari, "graf_odev.c", 0);
            addFile(veriYapilari, "stack_odev.c", 0);

        // 1.2 Algoritma
        addFile(odevler, "Algoritma", 1);

        // 1.3 Odev Listesi
        addFile(odevler, "odev_listesi.docx", 0);


    // 2. OYUNLAR KLASÖRÜ VE ALTINDAKİLER
    addFile(root, "Oyunlar", 1);
    File* oyunlar = root->child; // Oyunlar node'unu yakaladık

        // 2.1 GTA5
        addFile(oyunlar, "GTA5", 1);
        File* gta5 = oyunlar->child;
        addFile(gta5, "gta5.exe", 0);
        addFile(gta5, "saves", 1);

        // 2.2 Minecraft
        addFile(oyunlar, "Minecraft", 1);


    // 3. MUZİKLER KLASÖRÜ
    addFile(root, "Muzikler", 1);
    File* muzikler = root->child;
    addFile(muzikler, "rock.mp3", 0);
    addFile(muzikler, "pop.mp3", 0);


    // 4. ROOT'TAKİ DİĞER DOSYALAR
    addFile(root, "notlar.txt", 0);
    addFile(root, "resim.jpg", 0);
}