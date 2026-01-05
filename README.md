# 📁 File Management System

C programlama dilinde Graf veri yapısı kullanılarak geliştirilmiş bir dosya yönetim sistemi simülatörü.

## 🔧 Gereksinimler

- **GCC Derleyicisi** (MinGW veya TDM-GCC)
- Windows işletim sistemi

### GCC Kurulumu (Windows)

1. https://winlibs.com/ adresinden GCC'yi indirin
2. ZIP dosyasını `C:\mingw64` klasörüne çıkarın
3. `C:\mingw64\bin` yolunu Windows PATH'e ekleyin

**Kontrol:**
```powershell
gcc --version
```

## 🚀 Derleme ve Çalıştırma

```powershell
# Proje klasörüne git
cd FileManagementSystem

# Tüm dosyaları derle
gcc main.c File-Functions.c recycle.c menu.c loading.c color.c -o program.exe

# Çalıştır
./program.exe
```

### Derleme Seçenekleri

| Durum | Komut |
|-------|-------|
| **Tüm Proje** | `gcc main.c File-Functions.c recycle.c menu.c loading.c color.c -o program.exe` |
| **Quick Test** | VS Code'da `F5` tuşu ile otomatik derleme ve çalıştırma |

## 📋 Özellikler

### Geri Dönüşüm Kutusu Sistemi (Queue)
- **Dosya Silme:** Pointer kaydırma ile geri dönüşüm kutusuna taşıma (ENQUEUE)
- **Geri Yükleme:** Orijinal konumuna geri getirme (DEQUEUE)
- **Otomatik Temizlik:** Zaman aşımı sonrası kalıcı silme (FIFO)
- **POSTFIX Algoritması:** Yol temizleme

### Hash Table ile Hızlı Arama
- Zincirleme (Chaining) yöntemi ile çakışma çözümü
- O(1) ortalama arama süresi

### Dizin Görünümü
- Ağaç yapısında (tree view) hiyerarşik gösterim
- Klasörler `[köşeli parantez]` içinde
- Renkli çıktı desteği

## 📂 Dosya Yapısı

```
FileManagementSystem/
├── header.h          # Struct tanımları ve fonksiyon prototipleri
├── File-Functions.c  # Dosya işlemleri fonksiyonları
├── recycle.c         # Geri dönüşüm kutusu fonksiyonları
├── menu.c            # Menü sistemi
├── loading.c         # Loading screen
├── color.c           # Renk fonksiyonları
└── main.c            # Ana program
```

## 🗃️ Veri Yapıları

### File Struct (Graf Node'u)
```c
typedef struct File {
    char name[MAX_FILENAME];
    int isFolder;
    time_t deletedTime;                 // Silinme zamanı
    char originalPath[MAX_PATH_LENGTH]; // Orijinal konum
    struct File* parent;                // Üst dizin
    struct File* sibling;               // Kardeş dosya
    struct File* child;                 // Alt dosya
} File;
```

### RecycleBin Struct (Queue)
```c
typedef struct RecycleBin {
    File* root;             // Kuyruğun başı (front)
    File* tail;             // Kuyruğun sonu (rear)
    int itemCount;
    int timeoutSeconds;
} RecycleBin;
```

### HashNode Struct (Hash Table)
```c
typedef struct HashNode {
    char name[MAX_FILENAME];
    File* filePtr;
    struct HashNode* next;  // Zincirleme için
} HashNode;
```

## 👥 Ekip

| İsim | Modül |
|------|-------|
| **Mertcan Gündoğan** | Dosya işlemleri (Graph) |
| **Ahmet Eray Bekar** | Dosya Bulma (Hash Table) |
| **Volkan Taştemir** | Geri Dönüşüm Kutusu (Queue) |

---

*Veri Yapıları Dersi Projesi - 2025*
