#include <stdio.h>
#include <stdlib.h>

//NODE YAPISI (TREE İÇİN)
typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
}Node;




//YENİ NODE OLUŞTURMA FONKSİYONU
Node* newNode(int value){
    Node* newNode = malloc(sizeof(Node));
    newNode->value=value;
    newNode->right=NULL;
    newNode->left=NULL;

    return newNode;
}




//NODE'LARI TREE'YE KOYMA FONKSİYONU
Node* tree(Node* head,Node* node){
    if(head==NULL){
        printf("Deger eklendi: %d\n",node->value);
        return node;
    }

    if(head->value>node->value){
        head->left=tree(head->left,node);
    }else if(head->value<node->value){
        head->right=tree(head->right,node);
    }
    return head;
}

//GEZME FONKSİYONLARI
void preorder(Node* head){
    if(head==NULL)return;

    printf("%d ",head->value);
    preorder(head->left);
    preorder(head->right);
}
void inorder(Node* head){
    if(head==NULL)return;

    inorder(head->left);
    printf("%d ",head->value);
    inorder(head->right);
}
void postorder(Node* head){
    if(head==NULL)return;

    postorder(head->left);
    postorder(head->right);
    printf("%d ",head->value);
}


int main(void){
    int nums[7]; //tree'ye dönüştürülecek dizi (sonra direkt tree'ye dönüştürülebilir.)
    int adet = 0;
    char ayrac;
    Node* nood = NULL;
    printf("Sayilari bosluk birakarak girin ve Enter'a basin: ");

    do {
        scanf("%d%c", &nums[adet], &ayrac);
        adet++;
    } while (ayrac != '\n' && adet < 7);

    Node* head=NULL;

    for(int i=0;i<7;i++){
        nood=newNode(nums[i]);
        head=tree(head,nood);
    }

    printf("\n-------------------PREORDER----------------------\n");
    preorder(head);
    printf("\n-------------------INORDER----------------------\n");
    inorder(head);
    printf("\n-------------------POSTORDER----------------------\n");
    postorder(head);
    printf("\n-------------------ACIKLAMA----------------------\n");
    printf("Tree, kucuk degerler sola, buyuklar degerler saga yerlesecek sekilde olusturuldugu\nicin inorder, yani sol-kok-sag seklinde tarama fonksiyonu degerleri kucukten buyuge sıralamistir. ");
}