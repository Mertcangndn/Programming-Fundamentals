#ifndef HEADER_H
#define HEADER_H

//Node Struct
typedef struct PrintJob {
char fileName[50];
struct PrintJob* next;
}PrintJob;

typedef struct Queue {
PrintJob* front;
PrintJob* rear;
}Queue;

//Fonksiyon Header'leri
void enqueuePrintJob(Queue* q, char* dosyaAdi);
void processNextJob(Queue* q);
void showQueue(Queue q);

#endif