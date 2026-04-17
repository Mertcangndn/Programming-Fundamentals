#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

//Ekleme Fonksiyonu
void insertAt(Node** head , int value, int indis){
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
    Node* undoTempNode = NULL;
    for(int i=0 ; i!=indis ; i++){
        undoTempNode = tempNode;

        if(tempNode->next==NULL){   //Sona geldiyse
            tempNode->next = newNode;
            printf("Veri Başarıyla Eklendi!");
            return;
        }

        tempNode = tempNode->next;

        
    }

    //Insert işlemi
    if(indis!=0){   //Başta değilse
        undoTempNode->next=newNode;
        newNode->next=tempNode;
        printf("Veri Başarıyla Eklendi!");
        return;
    }else{  //Baştaysa
        newNode->next = tempNode;
        (*head) = newNode;
    }

}

//Verilen değerdeki ilk node'u siler
void deleteAt(Node** head, int value, int indis){
    Node* undoTempNode = NULL;
    Node* tempNode = *head;

    if(*head == NULL){   //head yoksa
        printf("iŞLEM YAPILAMADI!");
        return;
    }

    for(int i=0 ; i!=indis ; i++){
        undoTempNode = tempNode;

        if(tempNode->next==NULL){   //Sona geldiyse
            printf("iŞLEM YAPILAMADI!");
            return;
        }

        tempNode = tempNode->next;

        
    }

    if(undoTempNode!=NULL){ //Baştaki değilse
        undoTempNode->next=tempNode->next;
        free(tempNode);
        printf("\n\nNODE SİLİNDİ!\n\n");
        return;
    }else{  //Baştakiyse
        *head = tempNode->next;
        free(tempNode);
    }

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
    int indis;
    Node* x = malloc(sizeof(Node));
    x->value = 0;
    x->next = NULL;
    Node* tempNode = x;
    
    //Hazır Node Oluşturma
    for(int i=1 ; i<=10 ; i++){
        Node* nextTempNode = malloc(sizeof(Node));
        nextTempNode->value = 0;
        nextTempNode->next = NULL;
        tempNode->value = i;
        tempNode->next = nextTempNode;
        tempNode = tempNode->next;
    }
    printf("\n\nHazır Node'lar Oluşturuldu!\n\n");
    
    while(1){
        printf("\n\n\nBir Sayı giriniz:\n");
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
                printf("Eklemek istediğiniz indis [0-sonsuz): ");
                scanf("%d",&indis);
                insertAt(&x,value,indis);
                break;
            case 2:
                printList(x);
                break;
            case 3:
                printf("Bir İndis Girin: ");
                scanf("%d",&value);
                deleteAt(&x,value,indis);
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


