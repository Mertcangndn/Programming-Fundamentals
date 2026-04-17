# 🔀 Palindrom Sayı Denetleyicisi (Stack Kullanarak)

Bu proje, bir tam sayının palindromik (baştan ve sondan okunuşu aynı) olup olmadığını, **Stack (Yığın)** veri yapısı kullanarak kontrol eden bir [C / Java / Python - Kullandığınız Dili Buraya Yazın] uygulamasıdır.

Proje, veri yapılarının temel prensiplerinden biri olan **LIFO (Last-In, First-Out)** mantığının pratik bir uygulamasını göstermeyi amaçlamaktadır.

## 📝 Proje Açıklaması

Bir sayının palindrom olup olmadığını anlamak için sayının ters çevrilmiş hali ile orijinal halinin karşılaştırılması gerekir. Bu projede, sayının tersini elde etmek için bir **Stack** yapısı kullanılmaktadır.

Stack (Yığın) yapısı, **Node (Düğüm)** adı verilen birimlerden oluşan bir Bağlı Liste (Linked List) altyapısı üzerine kurulmuştur.

### ⚙️ Çalışma Mantığı (Algoritma)

1.  **Giriş:** Kullanıcıdan pozitif bir tam sayı alınır (Örn: `12321`).
2.  **Stack'e Ekleme (Push):** Sayının her bir basamağı (sondan başa doğru veya baştan sona fark etmez) tek tek stack'e `push` edilir.
    * `1` -> `push(1)`
    * `2` -> `push(2)`
    * `3` -> `push(3)`
    * `2` -> `push(2)`
    * `1` -> `push(1)`
    * (Stack'in tepesinde `1` olacaktır)
3.  **Stack'ten Çıkarma (Pop):** Stack'ten LIFO kuralına göre (sondan eklenen ilk çıkar) tüm elemanlar `pop` edilerek yeni bir sayı veya string oluşturulur.
    * `pop()` -> `1`
    * `pop()` -> `2`
    * `pop()` -> `3`
    * `pop()` -> `2`
    * `pop()` -> `1`
    * Oluşan yeni sayı (veya string): `12321`
4.  **Karşılaştırma:** Orijinal sayı (`12321`) ile stack'ten elde edilen sayı (`12321`) karşılaştırılır.
5.  **Sonuç:** Sayılar eşitse "Palindrom", değilse "Palindrom Değil" sonucu ekrana yazdırılır.



## 🛠️ Kullanılan Veri Yapıları

Bu projede temel Stack (Yığın) işlemleri için özel bir veri yapısı tasarlanmıştır.

* **Node (Düğüm):**
    * `int data`: Sayının bir basamağını tutar.
    * `Node* next` (veya `Node next`): Bir sonraki düğümü gösteren işaretçi (pointer).
* **Stack (Yığın):**
    * `Node* top` (veya `Node top`): Yığının en üstündeki (son giren) elemanı gösterir.
    * `void push(int data)`: Yığının tepesine yeni bir düğüm (node) ekler.
    * `int pop()`: Yığının tepesindeki düğümü çıkarır ve verisini döndürür.
    * `boolean isEmpty()`: Yığının boş olup olmadığını kontrol eder.
