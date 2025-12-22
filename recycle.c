#include "header.h"

// ============================================================
// GERİ DÖNÜŞÜM KUTUSU (RECYCLE BIN) FONKSİYONLARI
// ============================================================

// Yardımcı fonksiyon: Bir klasörün altındaki toplam dosya/klasör sayısını hesaplar (recursive)
int countChildren(File* file) {
    if (file == NULL) return 0;
    
    int count = 0;
    File* child = file->child;
    
    while (child != NULL) {
        count++;  // Bu child'ı say
        if (child->isFolder) {
            count += countChildren(child);  // Alt klasörün içeriğini de say
        }
        child = child->sibling;
    }
    
    return count;
}

// Geri dönüşüm kutusu başlatma
RecycleBin* initRecycleBin(int timeoutSeconds) {
    RecycleBin* bin = malloc(sizeof(RecycleBin));
    
    bin->root = NULL;
    bin->itemCount = 0;
    bin->timeoutSeconds = timeoutSeconds;
    
    return bin;
}

// Dosya yolunu oluşturma (POSTFIX için yardımcı fonksiyon)
// Parent zincirini takip ederek tam yolu oluşturur
void buildPath(File* file, char* buffer) {
    if (file == NULL) {
        buffer[0] = '\0';
        return;
    }
    
    // Stack benzeri yapı için recursive kullanıyoruz
    // Önce parent'ın yolunu al, sonra kendi ismini ekle
    if (file->parent != NULL) {
        buildPath(file->parent, buffer);
        strcat(buffer, "/");
    }
    strcat(buffer, file->name);
}

// Yardımcı fonksiyon: Dosyayı tüm alt klasörlerde recursive olarak arar
// Bulursa dosyanın parent'ını döndürür, bulamazsa NULL
File* findFileParent(File* current, char* fileName) {
    if (current == NULL) return NULL;
    
    // Bu node'un child'larında ara
    File* child = current->child;
    while (child != NULL) {
        if (strcmp(child->name, fileName) == 0) {
            return current;  // Bulduk! Parent'ı döndür
        }
        child = child->sibling;
    }
    
    // Child klasörlerin içinde recursive ara
    child = current->child;
    while (child != NULL) {
        if (child->isFolder) {
            File* found = findFileParent(child, fileName);
            if (found != NULL) return found;
        }
        child = child->sibling;
    }
    
    return NULL;  // Bulunamadı
}

// Pointer kaydırma ile dosyayı geri dönüşüm kutusuna taşıma
// Başarılı: 1, Başarısız: 0
// NOT: Bu fonksiyon tüm alt klasörlerde recursive arama yapar
int deleteFile(File* root, char* fileName, RecycleBin* bin) {
    if (root == NULL || bin == NULL) {
        return 0;  // Geçersiz parametre
    }
    
    // Dosyanın parent'ını bul (tüm alt klasörlerde ara)
    File* parent = findFileParent(root, fileName);
    
    if (parent == NULL) {
        printf("[HATA] Dosya bulunamadi: %s\n", fileName);
        return 0;
    }
    
    // Dosyayı parent'ın child zincirinde bul
    File* current = parent->child;
    File* previous = NULL;
    
    while (current != NULL && strcmp(current->name, fileName) != 0) {
        previous = current;
        current = current->sibling;
    }
    
    // ---- POINTER KAYDIRMA ----
    // Dosyayı parent'ın child zincirinden çıkar
    if (previous == NULL) {
        // İlk child ise
        parent->child = current->sibling;
    } else {
        // Ortada veya sonda ise
        previous->sibling = current->sibling;
    }
    
    // Bağlantıları kes
    current->sibling = NULL;
    current->parent = NULL;
    
    // Silinme zamanını kaydet
    current->deletedTime = time(NULL);
    
    // Orijinal yolu kaydet (geri yükleme için)
    buildPath(parent, current->originalPath);
    
    // ---- GERİ DÖNÜŞÜM KUTUSUNA EKLE ----
    // Geri dönüşüm kutusunun root'una ekle (en başa)
    current->sibling = bin->root;
    bin->root = current;
    bin->itemCount++;
    
    printf("[SILINDI] '%s' geri donusum kutusuna tasindi.\n", fileName);
    return 1;
}

// POSTFIX algoritması ile yol temizleme
// Aşağıdan yukarıya doğru recursive olarak temizler
void clearPath(File* file) {
    if (file == NULL) {
        return;
    }
    
    // POSTFIX: Önce child'ları temizle (aşağıdan yukarıya)
    if (file->child != NULL) {
        clearPath(file->child);
        file->child = NULL;
    }
    
    // Sonra sibling'leri temizle
    if (file->sibling != NULL) {
        clearPath(file->sibling);
        file->sibling = NULL;
    }
    
    // En son kendini temizle
    file->originalPath[0] = '\0';  // Yolu temizle
    file->deletedTime = 0;         // Zamanı sıfırla
}

// Yardımcı fonksiyon: İsme göre dosyayı tüm ağaçta recursive ara
File* findFileByName(File* current, char* name) {
    if (current == NULL) return NULL;
    
    // Bu node kontrolü
    if (strcmp(current->name, name) == 0) {
        return current;
    }
    
    // Child'larda ara
    File* child = current->child;
    while (child != NULL) {
        File* found = findFileByName(child, name);
        if (found != NULL) return found;
        child = child->sibling;
    }
    
    return NULL;
}

// Geri dönüşüm kutusundaki dosyayı geri yükleme
// Başarılı: 1, Başarısız: 0
int restoreFile(RecycleBin* bin, char* fileName, File* root) {
    if (bin == NULL || bin->root == NULL || root == NULL) {
        return 0;
    }
    
    File* current = bin->root;
    File* previous = NULL;
    
    // Dosyayı geri dönüşüm kutusunda bul
    while (current != NULL && strcmp(current->name, fileName) != 0) {
        previous = current;
        current = current->sibling;
    }
    
    // Dosya bulunamadı
    if (current == NULL) {
        printf("[HATA] Dosya geri donusum kutusunda bulunamadi: %s\n", fileName);
        return 0;
    }
    
    // Orijinal konumu bul
    char originalPath[MAX_PATH_LENGTH];
    strcpy(originalPath, current->originalPath);
    File* targetParent = root;
    
    // originalPath'ten son klasör adını bul
    // Örnek: "C:/Oyunlar/GTA5" -> "GTA5" parent olmalı
    if (strlen(originalPath) > 0) {
        char* lastSlash = strrchr(originalPath, '/');
        if (lastSlash != NULL) {
            // Son slash'tan sonraki kısım = parent klasör adı
            char parentName[MAX_FILENAME];
            strcpy(parentName, lastSlash + 1);
            
            if (strlen(parentName) > 0) {
                // Bu isimle klasörü bul
                File* foundParent = findFileByName(root, parentName);
                if (foundParent != NULL && foundParent->isFolder) {
                    targetParent = foundParent;
                }
            }
        } else {
            // Slash yok demek root altında
            // originalPath doğrudan parent adı olabilir (örn: "C:")
            if (strcmp(originalPath, root->name) != 0) {
                File* foundParent = findFileByName(root, originalPath);
                if (foundParent != NULL && foundParent->isFolder) {
                    targetParent = foundParent;
                }
            }
        }
    }
    
    // ---- GERİ DÖNÜŞÜM KUTUSUNDAN ÇIKAR ----
    if (previous == NULL) {
        bin->root = current->sibling;
    } else {
        previous->sibling = current->sibling;
    }
    bin->itemCount--;
    
    // ---- ORİJİNAL KONUMA GERİ EKLE ----
    current->sibling = targetParent->child;
    targetParent->child = current;
    current->parent = targetParent;
    
    // Geri dönüşüm kutusu bilgilerini temizle
    current->deletedTime = 0;
    current->originalPath[0] = '\0';
    
    printf("[GERI YUKLENDI] '%s' -> '%s' altina geri yuklendi.\n", fileName, targetParent->name);
    return 1;
}

// Otomatik temizlik - Zamanı dolan dosyaları kalıcı olarak siler
// NOT: Bu fonksiyon arka planda sessizce çalışır, sadece silme olduğunda bildirim verir
void autoCleanRecycleBin(RecycleBin* bin) {
    if (bin == NULL || bin->root == NULL) {
        return;
    }
    
    time_t currentTime = time(NULL);
    File* current = bin->root;
    File* previous = NULL;
    
    while (current != NULL) {
        // Zaman aşımı kontrolü
        double elapsedSeconds = difftime(currentTime, current->deletedTime);
        
        if (elapsedSeconds >= bin->timeoutSeconds) {
            // Zaman aşımı - Kalıcı olarak sil
            printf("\n[OTOMATIK SILINDI] '%s' suresi doldu ve kalici olarak silindi.\n", 
                   current->name);
            
            File* toDelete = current;
            
            // Listeden çıkar
            if (previous == NULL) {
                bin->root = current->sibling;
                current = bin->root;
            } else {
                previous->sibling = current->sibling;
                current = previous->sibling;
            }
            bin->itemCount--;
            
            // POSTFIX ile temizle ve belleği serbest bırak
            clearPath(toDelete);
            freeFile(toDelete);
        } else {
            // Sonraki dosyaya geç
            previous = current;
            current = current->sibling;
        }
    }
}

// Bellek temizleme (recursive)
// Dosyayı ve tüm alt öğelerini siler
void freeFile(File* file) {
    if (file == NULL) {
        return;
    }
    
    // Önce child'ları sil (recursive)
    if (file->child != NULL) {
        freeFile(file->child);
    }
    
    // Sonra sibling'leri sil (recursive)
    if (file->sibling != NULL) {
        freeFile(file->sibling);
    }
    
    // En son kendini sil
    free(file);
}

// Geri dönüşüm kutusunu listeleme
void listRecycleBin(RecycleBin* bin) {
    if (bin == NULL) {
        printf("[HATA] Geri donusum kutusu baslatilamadi!\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("       GERI DONUSUM KUTUSU\n");
    printf("========================================\n");
    printf("Dosya Sayisi: %d\n", bin->itemCount);
    printf("Zaman Asimi: %d saniye\n", bin->timeoutSeconds);
    printf("----------------------------------------\n");
    
    if (bin->root == NULL) {
        printf("(Geri donusum kutusu bos)\n");
    } else {
        File* current = bin->root;
        time_t currentTime = time(NULL);
        int index = 1;
        
        while (current != NULL) {
            double elapsedSeconds = difftime(currentTime, current->deletedTime);
            double remainingSeconds = bin->timeoutSeconds - elapsedSeconds;
            
            printf("\n%d. ", index++);
            if (current->isFolder) {
                int childCount = countChildren(current);
                printf("[Klasor] %s", current->name);
                if (childCount > 0) {
                    printf(" (%d alt oge ile birlikte)", childCount);
                }
                printf("\n");
            } else {
                printf("[Dosya]  %s\n", current->name);
            }
            printf("   Orijinal Konum: %s\n", current->originalPath);
            printf("   Kalan Sure: %.0f saniye\n", remainingSeconds > 0 ? remainingSeconds : 0);
            
            current = current->sibling;
        }
    }
    
    printf("\n========================================\n");
}