#include <stdio.h>
#include <stdlib.h>

//Temel Node Yapısı
typedef struct Node{
    int value; //Bu hangi düğüm
    struct Node* next;
}Node;

//Node Oluşurma Fonksiyonu
Node* createNode(int value){
    Node* newNode = malloc(sizeof(Node));
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}

//Temel Graph Yapısı
typedef struct Graph{
    int totalNode; //Graftaki toplam düğüm sayısını tutan değişken
    struct Node** adjLists; //Pointer dizisi (LinkedList'lerin başı)
    int* visited;   //BFS veya DFS arama yaparken ziyaret edilen node'ları tutar.
}Graph;

//Graph Oluşturma Fonksiyonu
Graph* createGraph(int totalNode){
    Graph* graph = malloc(sizeof(Graph));   //graph için yer açma
    
    graph->totalNode = totalNode;
    graph->adjLists = malloc(totalNode * sizeof(Node)); //graph'ın adjlayer'i için yer açma (toplam node sayısı * 1 Node büyüküğü kdr)
    graph->visited = malloc(totalNode * sizeof(int));   //graph'ın gezilenlari tutma listesi için yer açma (toplam node sayısı * 1 int büyüklüğü)

    //adjList'i ve visited listelerini doldurma
    for(int i=0 ; i<totalNode ; i++){
        graph->adjLists[i]=NULL; //Başlangıçta hiçbir node birbirine bağlı değil
        graph->visited[i]=0; //Başlangıçta hiçbir node ziyaret edilmedi (gezilmedi)
    }

    return graph;
}

//Graph'a node ekleme fonksiyonu
void addEdge(Graph* graph, int src, int dest){

    // Kaynaktan Hedefe (src -> dest) bağ ekle
    Node* newNode = createNode(dest);   //yeni node oluşturuldu (src eskiden vardı, dest oluşturuldu ve src'ye bağlanacak)
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    //Eğer yönsüz graph ise tam tersini de eklemelisin. (dest -> src)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(Graph* graph){
    for(int i=0 ; i<graph->totalNode ; i++){
        Node* tempNode = graph->adjLists[i];

        printf("%d. Node: ", i);

        while (tempNode) {
            printf("%d -> ", tempNode->value);
            tempNode = tempNode->next;
        }
        printf("NULL\n");
    }
}

//DFS Depth First Search Fonksiyonu
void DFS(Graph* graph, int start){  //start: hangi düğümden aramaya başlanacağıdır.

    // ADIM 1: Geldiğim yeri işaretle ve yazdır
    graph->visited[start]=1;
    printf("%d->",start);

    // ADIM 2: Komşulara bak
    Node* tempNode = graph->adjLists[start];
    while(tempNode){
        int neighborNode = tempNode->value;
        
        // ADIM 3: Eğer o komşuya daha önce girmediysen o yönde git.
        if(graph->visited[neighborNode]==0){
            DFS(graph, neighborNode); //Rekürsif kısım
        }

        //Sonraki Komşuya Geç
        tempNode=tempNode->next;
    }
}

//BFS Breadth First Search Fonksiyonu
void BFS(Graph* graph, int start){

    // ADIM 1: Önce visited listesini temizleyelim (DFS'ten kalan izler silinsin)
    for (int i = 0; i < graph->totalNode; i++)graph->visited[i] = 0;

    // --- KUYRUK KURULUMU (Manuel Queue) ---
    int queue[100]; // 100 kişilik bir bekleme sırası
    int front = 0;  // Sıranın başı (Gişe)
    int rear = 0;   // Sıranın sonu (Yeni gelenin gireceği yer)

    // ADIM 2: Başlangıç düğümünü sıraya al ve işaretle
    graph->visited[start]=1;
    queue[rear] = start;
    rear++; //Sıra bir kişi uzadı

    // ADIM 3: Sırada bekleyen hiçbir node kalmayana kadar devam et.
    while(front<rear){

        //Sıradakini çağırma (dequeue)
        int currentNode = queue[front];
        printf("%d->",currentNode);
        front++; //Sıra ilerledi

        // Bu elemanın komşularını bul ve sıraya ekle
        Node* tempNode = graph->adjLists[currentNode];

        while(tempNode){
            int neighborNode = tempNode->value;

            //Eğer komşu daha önce ziyaret edilmediyse
            if(graph->visited[neighborNode] == 0){
                graph->visited[neighborNode] = 1;  //ziyaret edildi diye değiştir.
                queue[rear] = neighborNode; //sıraya sok
                rear++;
            }
            tempNode = tempNode->next;
        }
    }
    printf("NULL");
    printf("\n");
}


int main(void){

    Graph* graph = createGraph(6);
    
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);

    printGraph(graph);

    printf("\n DFS: ");
    DFS(graph, 0); //0. node'dan başla.
    printf("\n BFS: ");
    BFS(graph, 0);

    return 0;
}