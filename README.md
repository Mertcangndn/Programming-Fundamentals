# 📁 File Management System - Geri Dönüşüm Kutusu

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

# Derle
gcc main.c File-Functions.c -o test.exe

# Çalıştır
./test.exe
```

## 📋 Özellikler

### Geri Dönüşüm Kutusu Sistemi
- **Dosya Silme**: Pointer kaydırma ile geri dönüşüm kutusuna taşıma
- **Geri Yükleme**: Orijinal konumuna geri getirme
- **Otomatik Temizlik**: Zaman aşımı sonrası kalıcı silme
- **POSTFIX Algoritması**: Yol temizleme

### Dizin Görünümü
- Ağaç yapısında (tree view) hiyerarşik gösterim
- Klasörler `[köşeli parantez]` içinde
- Recursive derinlik desteği

## 📂 Dosya Yapısı

```
FileManagementSystem/
├── header.h          # Struct tanımları ve fonksiyon prototipleri
├── File-Functions.c  # Tüm fonksiyon implementasyonları
├── main.c            # Test menüsü
├── menu.c            # Menü fonksiyonu
├── loading.c         # Loading screen
└── color.c           # Renk fonksiyonları
```

## 🗃️ Veri Yapıları

### File Struct
```c
typedef struct File {
    char name[MAX_FILENAME];
    int isFolder;
    time_t deletedTime;              // Silinme zamanı
    char originalPath[MAX_PATH];     // Orijinal konum
    struct File* parent;
    struct File* sibling;
    struct File* child;
} File;
```

### RecycleBin Struct
```c
typedef struct RecycleBin {
    File* root;
    int itemCount;
    int timeoutSeconds;
} RecycleBin;
```

## 👥 Ekip

| İsim | Modül |
|------|-------|
| **Volkan Taştemir** | Geri Dönüşüm Kutusu |
| **Mertcan Gündoğan** | - |
| **Ahmet Eray Bekar** | - |

---

*Veri Yapıları Dersi Projesi - 2025*
