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

//PREORDE KOPYA FONKSİYONU 
Node* preorder(Node* head){
    if(head==NULL)return head;

    Node* tempNode = newNode(head->value);

    tempNode = tree(head,tempNode);
    head->left=preorder(head->left);
    head->right=preorder(head->right);
    return head;
}


//INORDER YAZDIRMA FONKSİYONU
void inorder(Node* head){
    if(head==NULL)return;

    inorder(head->left);
    printf("%d ",head->value);
    inorder(head->right);
}


//POSTORDER SİLME FONKSİYONU
void postorder(Node** head){
    if(*(head)==NULL)return;

    postorder(&((*head)->left));
    postorder(&((*head)->right));
    free(*head);
}


int main(void){
    int nums[6]; //tree'ye dönüştürülecek dizi (sonra direkt tree'ye dönüştürülebilir.)
    int adet = 0;
    char ayrac;
    Node* nood = NULL;
    Node* copy = NULL;
    printf("Sayilari bosluk birakarak girin ve Enter'a basin: ");

    do {
        scanf("%d%c", &nums[adet], &ayrac);
        adet++;
    } while (ayrac != '\n' && adet < 7);

    Node* head=NULL;

    for(int i=0;i<6;i++){
        nood=newNode(nums[i]);
        head=tree(head,nood);
    }

    copy = preorder(head);
    printf("\n-------------------PREORDER KOPYALAMA BASARİLİ----------------------\n");

    printf("\n-------------------INORDER YAZDIRMA----------------------\n");
    printf("Orijinal Agac: ");
    inorder(head);
    printf("\n");
    printf("Kopya Agac: ");
    inorder(copy);
    printf("\n-----------------------------------------\n");
    postorder(&head);
    printf("\n-------------------POSTORDER SILME BASARİYLA YAPİLDİ----------------------\n");
}