#include "header.h"

int main(void){
    int choice;
    char fileName[MAX_FILENAME];
    
    loadingScreen();    //test aşamasında kolayca çalıştırıp denemek için yorum satırına alınabilir.
    // menu();

    // ------ DOSYA YAPISI OLUŞTURMA (Derin Hiyerarşi) -------
    // NOT: changeDirectory fonksiyonu beklendiği gibi çalışmadığı için
    // createFile ve pointer atamaları kullanılarak hiyerarşi oluşturuldu
    
    File* root = createFile("C:",1);
    
    // === 1. SEVİYE: Root altındaki klasörler ve dosyalar ===
    File* odevler = createFile("Odevler", 1);
    File* oyunlar = createFile("Oyunlar", 1);
    File* muzikler = createFile("Muzikler", 1);
    File* notlar = createFile("notlar.txt", 0);
    File* resim = createFile("resim.jpg", 0);
    
    // Root'un child zinciri: Odevler -> Oyunlar -> Muzikler -> notlar -> resim
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
    
    // === 2. SEVİYE: Odevler klasörü içeriği ===
    File* veriYapilari = createFile("VeriYapilari", 1);
    File* algoritma = createFile("Algoritma", 1);
    File* odevListesi = createFile("odev_listesi.docx", 0);
    
    odevler->child = veriYapilari;
    veriYapilari->parent = odevler;
    veriYapilari->sibling = algoritma;
    algoritma->parent = odevler;
    algoritma->sibling = odevListesi;
    odevListesi->parent = odevler;
    
    // === 3. SEVİYE: VeriYapilari klasörü içeriği ===
    File* proje1 = createFile("Proje1", 1);
    File* grafOdev = createFile("graf_odev.c", 0);
    File* stackOdev = createFile("stack_odev.c", 0);
    
    veriYapilari->child = proje1;
    proje1->parent = veriYapilari;
    proje1->sibling = grafOdev;
    grafOdev->parent = veriYapilari;
    grafOdev->sibling = stackOdev;
    stackOdev->parent = veriYapilari;
    
    // === 4. SEVİYE: Proje1 klasörü içeriği ===
    File* mainC = createFile("main.c", 0);
    File* headerH = createFile("header.h", 0);
    File* readme = createFile("README.md", 0);
    
    proje1->child = mainC;
    mainC->parent = proje1;
    mainC->sibling = headerH;
    headerH->parent = proje1;
    headerH->sibling = readme;
    readme->parent = proje1;
    
    // === 2. SEVİYE: Oyunlar klasörü içeriği ===
    File* gta5 = createFile("GTA5", 1);
    File* minecraft = createFile("Minecraft", 1);
    
    oyunlar->child = gta5;
    gta5->parent = oyunlar;
    gta5->sibling = minecraft;
    minecraft->parent = oyunlar;
    
    // === 3. SEVİYE: GTA5 klasörü içeriği ===
    File* gtaExe = createFile("gta5.exe", 0);
    File* saves = createFile("saves", 1);
    
    gta5->child = gtaExe;
    gtaExe->parent = gta5;
    gtaExe->sibling = saves;
    saves->parent = gta5;
    
    // === 2. SEVİYE: Muzikler klasörü içeriği ===
    File* rock = createFile("rock.mp3", 0);
    File* pop = createFile("pop.mp3", 0);
    
    muzikler->child = rock;
    rock->parent = muzikler;
    rock->sibling = pop;
    pop->parent = muzikler;

    // Geri dönüşüm kutusunu başlat (TEST için 30 saniye timeout)
    RecycleBin* bin = initRecycleBin(30);

    // ------ TEST MENÜSÜ -------
    while(1) {
        // Otomatik temizlik - her döngüde sessizce kontrol et
        autoCleanRecycleBin(bin);
        
        printf("\n\n===== GERI DONUSUM KUTUSU TEST MENUSU =====\n");
        printf("1. Mevcut Dizini Listele\n");
        printf("2. Dosya Sil (Geri Donusum Kutusuna Tasi)\n");
        printf("3. Geri Donusum Kutusunu Listele\n");
        printf("4. Dosyayi Geri Yukle\n");
        printf("5. Cikis\n");
        printf("============================================\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);
        getchar(); // Buffer temizle

        switch(choice) {
            case 1:
                printf("\n--- MEVCUT DIZIN ---\n");
                listDirectory(root);
                break;
                
            case 2:
                printf("\nSilinecek dosya adi: ");
                scanf("%s", fileName);
                deleteFile(root, fileName, bin);
                break;
                
            case 3:
                listRecycleBin(bin);
                break;
                
            case 4:
                printf("\nGeri yuklenecek dosya adi: ");
                scanf("%s", fileName);
                restoreFile(bin, fileName, root);
                break;
                
            case 5:
                printf("\nCikis yapiliyor...\n");
                return 0;
                
            default:
                printf("\nGecersiz secim!\n");
        }
    }

    return 0;
}