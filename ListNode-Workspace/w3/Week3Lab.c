#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

//Ekleme Fonksiyonu
void addOrdered(Node** head , int value){
    int temp;   //Swap işlemi için değişken
    
    //Yeni node oluşturma işlemi
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next=NULL;
    
    if(*head == NULL){   //head yoksa
        *head = newNode;
        printf("Veri Başarıyla Eklendi!");
        return;
    }
    

    Node* tempNode = *head; //Başlangıç noktasını kaybetmemek için geçici değişken
    while(1){
        if(newNode->value >= tempNode->value){//İleriye devam edecek
            if(tempNode->next==NULL){//eğer sona geldiysek
                tempNode->next=newNode;
                printf("Veri Başarıyla Eklendi!");
                return;
            }else{
                tempNode = tempNode->next;
                continue;
            }
        }else{
            temp = newNode->value;
            newNode->value = tempNode->value;
            tempNode->value = temp;
            continue;
        }
    }
}

//Verilen değerdeki ilk node'u siler
void removeNode(Node** head, int value){
    Node* undoTempNode = NULL;
    Node* tempNode = *head;

    while(tempNode != NULL){    //Node'lar bitmediği veya oluşturulduğu sürece
        if((tempNode->value==value)){   //Eşleşen karakter bulunduysa
            if(undoTempNode==NULL && tempNode->next!=NULL){ //İlk karakterle eşleşiyorsa ve devamı var
                *head = tempNode->next;
                free(tempNode);
                printf("\n\nNODE SİLİNDİ\n\n");
                return;
            }else if(undoTempNode==NULL && tempNode->next==NULL){ //tek karakterle eşleşiyorsa
                *head = NULL;
                printf("\n\nNODE SİLİNDİ\n\n");
                return;
            }else{
                undoTempNode->next = tempNode->next;
                free(tempNode);
                printf("\n\nNODE SİLİNDİ\n\n");
                return;
            }
        }else{
            undoTempNode = tempNode;
            tempNode = tempNode->next;
            continue;
        }
    }

    printf("\n\nNODE BULUNAMADI\n\n");
}

//Liste uzunluğunu yazdırma
int count(Node* head){
    int i = 0;
    
    while(head != NULL){
        i++;
        head = head->next;
    }
    
    return i;
}

//Yazdırma Fonksiyonu
void printList(Node* head){
    printf("\n\n----------------------------\n");
    while(head!=NULL){
        printf("%d ",head->value);
        head = head->next;
    }
    printf("\n----------------------------\n\n");
    return;
}

//Listeyi serbest bırakma
void clear(Node** head){
    
    if(*head != NULL){
        Node* nextNode = (*head)->next;
        while (*head!=NULL)
        {
            free(*head);
            *head = nextNode;

            if(nextNode != NULL){
                nextNode = nextNode->next;
            }else{
                break;
            }
            
        }
    }

    printf("\n\nNode'lar Temizlendi\n\n");
    
}

void menu(void){
    
    int value;
    int select;
    Node* x = NULL;
    
    while(1){
        printf("Bir Sayı giriniz:\n");
        printf("[1] Node Değeri Girişi Yap\n");
        printf("[2] Node'ları Oku\n");
        printf("[3] Node Sil\n");
        printf("[4] Node'ları Say\n");
        printf("[5] Node'ları Temizle\n");
        printf("[0] Çıkış Yap\n\n\n");
        
        scanf("%d",&select);
        
        switch(select){
            case 1:
                printf("Bir Value Girin: ");
                scanf("%d",&value);
                addOrdered(&x,value);
                break;
            case 2:
                printList(x);
                break;
            case 3:
                printf("Bir Value Girin: ");
                scanf("%d",&value);
                removeNode(&x,value);
                break;
            case 4:
                printf("\n\nNode sayısı = %d",count(x));
                printf("\n\n");
                break;
            case 5:
                clear(&x);
                break;
            case 0:
                if(x!=NULL){
                    while (x!=NULL && x->next==NULL){
                        Node* temp = x;
                        x = x->next;
                        free(temp);
                    }
                }
                return;
            default:
                printf("Yanlış Seçim, Lütfen Tekrar Deneyin.\n");
                break;
        }
    }
}

int main() {
    
    menu();
    

    return 0;
}


