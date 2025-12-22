#include "header.h"

void menu(void){
    //printf("FileManagementSystem\\admin> "); //her komutun başındaki prompt (çok uğraştırırsa kaldırabiliriz.) KOMUTLU SİSTEM İÇİN GEÇERLİ

    int choice;
    char fileName[MAX_FILENAME];
    
    File* root = createFile("C:",1);
    defaultPath(root);
    syncTreeToHash(root);

    //Geri dönüşüm kutusunu başlat (TEST için 30 saniye timeout)
    RecycleBin* bin = initRecycleBin(30);

    File* currentFile = root;   //Mevcutta bulunulan dizini tutan node

    //Asıl menü kısmı
    while(1) {
        // Otomatik temizlik - her döngüde sessizce kontrol et
        autoCleanRecycleBin(bin);
        
        printf("\n\n========= Dosya Yonetim Sistemi =========\n");
        printf("Current Folder: ");directoryPrinter(currentFile);
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
        scanf("%d", &choice);
        getchar(); // Buffer temizle

        switch(choice) {
            case 1:
                printf("\n--- Mevcut Dizin ---\n");
                listDirectory(currentFile);
                break;
            
            case 2:
                printf("\nDosya Ismi Giriniz: ");
                scanf("%s",fileName);

                if (strrchr(fileName, '.') != NULL) {   //isminde nokta varsa (code.py) dosya olarak, yoksa klasör olarak oluşturuyor.
                    addFile(currentFile,fileName,0);
                } else {
                    addFile(currentFile,fileName,1);
                }
                break;
                
            case 3:
                printf("\nSilinecek dosya adi: ");
                scanf("%s", fileName);
                deleteFile(root, fileName, bin);
                break;
            
            case 4:
                printf("\nDosya Ismi Giriniz: ");
                scanf("%s",fileName);
                if(changeDirectory(root,fileName)){
                    currentFile=changeDirectory(root,fileName);
                }else{
                    printf("\n\nGirilen Isimde Bir Dosya Bulunamadi!\n\n");
                }
                break;
                
            case 5:
                listRecycleBin(bin);
                break;
                
            case 6:
                printf("\nGeri yuklenecek dosya adi: ");
                scanf("%s", fileName);
                restoreFile(bin, fileName, root);
                break;
            
            case 7:
                printf("\nAradiginiz Dosyanin Adini Giriniz: ");
                scanf("%s", fileName);
                File* foundFile = findDirectory(fileName);

                if(foundFile!=NULL){
                    printTreeColored(root, "", 1, foundFile);
                }else{
                    printf("[HATA] Dosya bulunamadi!\n");
                }
                break;
                
            case 8:
                printf("\nCikis yapiliyor...\n");
                return;
                
            default:
                printf("\nGecersiz secim!\n");
        }
    }
    getch();
}

void defaultPath(File* root){
    File* odevler = createFile("Odevler", 1);
    File* oyunlar = createFile("Oyunlar", 1);
    File* muzikler = createFile("Muzikler", 1);
    File* notlar = createFile("notlar.txt", 0);
    File* resim = createFile("resim.jpg", 0);
    root->child = odevler;
    odevler->parent = root;
    odevler->sibling = oyunlar;
    oyunlar->parent = root;
    oyunlar->sibling = muzikler;
    muzikler->parent = root;
    muzikler->sibling = notlar;
    notlar->parent = root;
    notlar->sibling = resim;
    resim->parent = root;

    File* veriYapilari = createFile("VeriYapilari", 1);
    File* algoritma = createFile("Algoritma", 1);
    File* odevListesi = createFile("odev_listesi.docx", 0);
    odevler->child = veriYapilari;
    veriYapilari->parent = odevler;
    veriYapilari->sibling = algoritma;
    algoritma->parent = odevler;
    algoritma->sibling = odevListesi;
    odevListesi->parent = odevler;

    File* proje1 = createFile("Proje1", 1);
    File* grafOdev = createFile("graf_odev.c", 0);
    File* stackOdev = createFile("stack_odev.c", 0);
    veriYapilari->child = proje1;
    proje1->parent = veriYapilari;
    proje1->sibling = grafOdev;
    grafOdev->parent = veriYapilari;
    grafOdev->sibling = stackOdev;
    stackOdev->parent = veriYapilari;

    File* mainC = createFile("main.c", 0);
    File* headerH = createFile("header.h", 0);
    File* readme = createFile("README.md", 0);
    proje1->child = mainC;
    mainC->parent = proje1;
    mainC->sibling = headerH;
    headerH->parent = proje1;
    headerH->sibling = readme;
    readme->parent = proje1;
    
    File* gta5 = createFile("GTA5", 1);
    File* minecraft = createFile("Minecraft", 1);
    oyunlar->child = gta5;
    gta5->parent = oyunlar;
    gta5->sibling = minecraft;
    minecraft->parent = oyunlar;
    
    File* gtaExe = createFile("gta5.exe", 0);
    File* saves = createFile("saves", 1);
    gta5->child = gtaExe;
    gtaExe->parent = gta5;
    gtaExe->sibling = saves;
    saves->parent = gta5;

    File* rock = createFile("rock.mp3", 0);
    File* pop = createFile("pop.mp3", 0);
    muzikler->child = rock;
    rock->parent = muzikler;
    rock->sibling = pop;
    pop->parent = muzikler;
}