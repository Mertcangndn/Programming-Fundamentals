# C Dili ile Bağlı Liste (ListNode) Uygulaması

![Dil](https://img.shields.io/badge/Language-C-blue.svg)

Bu proje, C programlama dilini kullanarak temel bir **Tek Yönlü Bağlı Liste (Singly Linked List)** veri yapısının nasıl oluşturulacağını ve yönetileceğini gösteren bir konsol uygulamasıdır.

Proje, `malloc` ile dinamik bellek yönetimi kullanarak düğümler (Node'lar) oluşturur, bu düğümleri **sıralı** bir şekilde listeye ekler, listeyi yazdırır ve program sonlandığında ayrılan belleği `free` ile serbest bırakır.

## İçerik

* [Temel Veri Yapısı](#temel-veri-yapısı)
* [Fonksiyonlar](#fonksiyonlar)
* [Nasıl Kullanılır?](#nasıl-kullanılır)
    * [Gereksinimler](#gereksinimler)
    * [Derleme ve Çalıştırma](#derleme-ve-çalıştırma)
* [Olası Geliştirmeler](#olası-geliştirmeler)

## Temel Veri Yapısı

Projenin temeli, bir `int` değer ve bir sonraki düğümü işaret eden bir gösterici (pointer) içeren `Node` struct'ıdır.

```c
typedef struct Node {
    int value;
    struct Node* next;
} Node;
```

Listenin başını (`head`) takip etmek için `Node**` (pointer'a pointer) yapısı kullanılmıştır. Bu sayede `addOrdered` gibi fonksiyonlar, listenin başlangıç noktasını kalıcı olarak değiştirebilir.

## Fonksiyonlar

Proje, kullanıcı etkileşimli bir menü üzerinden aşağıdaki ana fonksiyonları kullanır:

* `void addOrdered(Node** head, int value)`
    Listeye yeni bir tamsayı değeri ekler. Ekleme işlemi küçükten büyüğe **sıralı** olarak yapılır. Yeni değer, listedeki doğru konumuna (başa,
