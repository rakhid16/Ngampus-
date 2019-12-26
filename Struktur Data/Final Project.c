#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node{                   // BUAT KESELURUHAN
	int data, kursi, nomor;
	char film[30], judul[30];
	struct node *next;
	struct node *right;
    struct node *left;
}; typedef struct node node;

struct queue{                  // BUAT QUEUE SAJA  
	int count;
	node *front;
	node *rear;
}; typedef struct queue queue;

queue createQueue(void) {      // BUAT QUEUE
	queue myQueue;
	myQueue.count=0;
	myQueue.front=NULL;
	myQueue.rear=NULL;
	return(myQueue);
}

int enqueue(int data, char film[30], queue *myQueue){   // MASUKKAN NILAI KE QUEUE
int success;
 
	if(myQueue->count>=99)
 		success=0;
 	
	else{
  		node *newPtr;
  		newPtr=(node*)malloc(sizeof(node));
  
  		newPtr->data=data;
  		strcpy(newPtr->film,film);
		
		newPtr->next=NULL;
  
		if(myQueue->front==NULL)
  			myQueue->front=newPtr;
  		else
	  		myQueue->rear->next=newPtr;
   
   		myQueue->rear=newPtr;
   		myQueue->count++;
   		success=1;
 	}return success;
}

node *createNode(void){                     // NODE BUAT QUEUE
	node *newPtr;
	newPtr=(node *)malloc(sizeof(newPtr));
	return(newPtr);
}

void destroy(queue *myQueue){                // DESTROY QUEUE
	node *temp;
	
	while(myQueue->count!=0){
		temp=myQueue->front;
		myQueue->front=myQueue->front->next;
		myQueue->count--;
		free(temp);
	}	
	myQueue->count=0;
	myQueue->front=NULL;
	myQueue->rear=NULL;
}

void display(queue myQueue){            // TAMPILKAN ANTRIAN
	node *temp;
	temp=myQueue.front;
	
	if (temp == NULL)
		printf("Kosong");
	
	else{
		printf("Antrian :\n");
		while(temp){
			printf("\nJudul film      %s\n",temp->film);
			printf("Nomor kursi     %d\n",temp->data);
			temp=temp->next;
		}
	}
}

// =============================================================================================================================================================

node *createnOde(int bil){   // NODE BUAT SINGLE LINKED LIST
	node *ptr;
	ptr = (node *)malloc(sizeof(node));
	
	if(ptr != NULL){
		ptr->kursi = bil;
		ptr->next = NULL;
	} return(ptr);
}

void insertNode(node **head, node *pPre, node *pNew){   // MASUKKAN DATA KE NODE - SINGLE LINKED LIST
    if (pPre == NULL){
	    pNew -> next = *head;
       *head = pNew;
    }
    else {
       pNew -> next = pPre -> next;
       pPre -> next = pNew;
   }
}

void deleteNode(node **head, node *pPre, node *pCur){   // HAPUS DATA KE NODE - SINGLE LINKED LIST
	if(pPre == NULL)
		*head = pCur -> next;
	else
		pPre->next = pCur->next;
	free(pCur);
}

void tranverse(node *head){   // TAMPILKAN DATA-DATA - SINGLE LINKED LIST
	node *pWalker;
	pWalker = head;
    system("cls");
	
	if(pWalker==NULL)
		printf("NULL");

	printf("Judul film berserta kursi yang tersisa :\n\n");
	printf("1. FORREST GUMP\n");
	while(pWalker != NULL){
		
		if (pWalker->kursi < 10){ // JIKA NILAI KURANG DARI 10
			printf("|0%d| ", pWalker -> kursi);
			goto w;
		}
		
		printf("|%d| ", pWalker -> kursi);w:
		pWalker = pWalker -> next;
		
		if(pWalker->kursi==31){
		pWalker = pWalker -> next;
		break;
		}
		
		if(pWalker->kursi >=31){
			system("cls");
			printf("Judul film berserta kursi yang tersisa :\n\n");
			printf("1. FORREST GUMP\n");
			printf("SEMUA KURSI SUDAH DIPESAN!");
			break;
		}
	} 
	
	printf("\n\n2. PAPER TOWN\n");
	while(pWalker != NULL){
		
		if (pWalker->kursi-31 < 10){ // JIKA NILAI KURANG DARI 10
			printf("|0%d| ", pWalker -> kursi-31);
			goto q;
		}
		
		if(pWalker->kursi >=31 && pWalker->kursi >=62){
			printf("SEMUA KURSI SUDAH DIPESAN!");
			pWalker=pWalker->next;
			break;
		}
		
		printf("|%d| ", pWalker -> kursi-31); q://-1
		pWalker = pWalker -> next;
		
		if(pWalker->kursi==62){
			pWalker = pWalker -> next;
			break;}
	}
	
	printf("\n\n3. VENOM\n");
	while(pWalker != NULL){
		
		if (pWalker->kursi-62 < 10){ // JIKA NILAI KURANG DARI 10
			printf("|0%d| ", pWalker -> kursi-62);
			goto e;
		}
		
		if(pWalker->kursi==93){
			printf("SEMUA KURSI SUDAH DIPESAN!");
			break;
		}
		
		printf("|%d| ", pWalker -> kursi-62); e://-1
		pWalker = pWalker -> next;
		
		if(pWalker->kursi==93){
			pWalker = pWalker -> next;
			break;}
			
		if(pWalker->kursi >=31 && pWalker->kursi >=62 && pWalker->kursi >=93){
			printf("SEMUA KURSI SUDAH DIPESAN!");
			break;
		}
	}
}

void deleteList(node *head){   // DESTROY SINGLE LINKED LIST
  node *pTemp;

  while(head != NULL){
     pTemp = head;
     head = head->next;
     free(pTemp);
  }
}

void hapusData(node **head, int kursi){   // MENGHAPUS DATA - SINGLE LINKED LIST
	node *pCur, *pPre;
	int pos;
	
	if(kursi>=31&&kursi<=60){
		kursi=kursi+1;
	}
	else if(kursi>=61&&kursi<93){
		kursi=kursi+2;
	}
	
	pPre = NULL;
	pCur = *head;
	
	while(pCur != NULL && pCur->kursi != kursi){
		pPre=pCur;
		pCur=pCur->next;
	}
	
	if(pCur!=NULL)
		deleteNode(head,pPre,pCur);
	else{
		printf("\nKursi itu sudah terpesan!");
		getch();
	}
}

// =============================================================================================================================================================

node *creatEnode(int bil, char judul[30]){  // BIKIN NODE BUAT BST
	node *pNew;
	
	pNew = (node *)malloc(sizeof(node));
	if (pNew != NULL){
    	pNew->nomor = bil;
    	strcpy(pNew->judul,judul);
    	pNew->left = NULL;
    	pNew->right = NULL;
	} return(pNew);
}

void insert(node **root, node *newNode){  // MASUKKAN DATA KE NODE - BST
	if(*root == NULL)
		*root = newNode;
	else if (newNode->nomor < (*root)->nomor)
		insert(&((**root).left), newNode);
	else
		insert(&((**root).right), newNode);
}

void inorder(node *root, int *a, int *b, int *c){   // TAMPILKAN DATA - BST
	
	if (root != NULL){
		inorder(root->left, a,b,c);
		if(strcmp(root->judul, "PAPER TOWN")==0)
			*b=*b+25000;
		else if(strcmp(root->judul, "VENOM")==0)
			*c=*c+30000;
		else
			*a=*a+20000;
		printf("%d\n", root->nomor);
		printf("%s\n\n", root->judul);		
		inorder(root->right, a,b,c);
	}
}

node *findLargestBST(node *root){    // BUAT BST
	if (root ->right == NULL)
		return(root);
	else
		return(findLargestBST(root->right));
}

bool deletenOde(node **root, int key){    // BUAT BST - MEMERLUKAN findLargestBST
	node *pDel;
	node *pReplace;

	if(*root == NULL)
		return(false);
	
	else if (key < (*root)->nomor)
		return(deletenOde(&((**root).left), key));
		
	else if (key > (*root)->nomor)
		return(deletenOde(&((**root).right), key));
		
	else{
		if ((*root)->left == NULL && (*root)->right == NULL){
		pDel = *root;
		*root = NULL;
		free(pDel);
		return(true);
    }
	
		else if ((*root)->left == NULL){
			pDel = *root;
			*root = (*root)-> right;
			free(pDel);
			return(true);
    	}
    
		else if ((*root)->right == NULL){
			pDel = *root;
			*root = (*root)-> left;
			free(pDel);
			return(true);
		}
	
		else{
			pDel = *root;
			pReplace = findLargestBST((*root)->left);
			pDel->nomor = pReplace->nomor;
			return (deletenOde(&((**root).left), pReplace->nomor));
		}
   }
}

void deleteBST(node **root){    // BUAT BST - MEMERLUKAN deletenOde
	while(*root != NULL)
		deletenOde(root, (*root)->nomor);
}

int cekcoy(node *root, int num, char judul[30], int cpksgd){   // TAMPILKAN DATA
	if (root != NULL){
		cpksgd=cekcoy(root->left, num, judul,cpksgd);
		
		if(num == root->nomor && strcmp(root->judul, judul)==0){
			cpksgd=0;
		}
		
		cpksgd=cekcoy(root->right, num, judul,cpksgd);
	} return(cpksgd);
}

// =============================================================================================================================================================

void dequeue(queue *myQueue, node **root, node **kursi){   // DELETE QUEUE
	node  *pNew;
	
	int dequeue;
	char film[30];
	if(myQueue->count==0)
		printf("\nTidak ada antrian");
		
	else{
		node *dltPtr;
		
		dltPtr = myQueue->front;
		dequeue = dltPtr->data;
		strcpy(film,dltPtr->film);
		
		myQueue->front=myQueue->front->next;
		free(dltPtr);
		myQueue->count--;
		printf("\nKursi nomor %d dari film %s terpesan!",dequeue, film);
		
		if(strcmp(film, "PAPER TOWN")==0){
			hapusData(kursi,dequeue+30);
		}
		else if(strcmp(film, "VENOM")==0){
			hapusData(kursi,dequeue+60);
		}
		else{
			hapusData(kursi,dequeue);
		}
		
		pNew = creatEnode(dequeue,film);
			if (pNew == NULL){
				printf("insert gagal");
				getch();
			}
			else
            	insert(root, pNew);
	}
}

void tampil(){
	printf("*ilustrasi ruangan                                ||\n");
	printf("                                                  ||\n");
	printf("            > > > LAYAR BIOSKOP < < <             ||\n");
	printf("                                                  ||\n");
	printf("|01| |02| |03| |04| |05| |06| |07| |08| |09| |10| ||\n");
	printf("                                                  ||\n");
	printf("|11| |12| |13| |14| |15| |16| |17| |18| |19| |20| ||\n");
	printf("                                                  ||\n");
	printf("|21| |22| |23| |24| |25| |26| |27| |28| |29| |30| ||\n");
	printf("                                                  ||\n");
	printf("            ^ ^ ^ BARISAN KURSI ^ ^ ^             ||\n");
	printf("                                                  ||\n");
	printf("====================================================\n\n");
}

//==============================================================================================================================================================

int main(){
	int choice,pilFilm, num, success,a,b,c;
	char film[30];
   	queue myQueue;
	int p; myQueue=createQueue();
	
	node *head, *ptr, *root;
	root=NULL;
	int bil, kursi;
	head = NULL;
	
	for (kursi=99; kursi>0; kursi--){
		bil=kursi-1;
		ptr = createnOde(bil+1);
			if (ptr == NULL){
				printf("insert gagal");
				getch();
			}
			else
				insertNode(&head, NULL, ptr);
	}
	
	do{z:
		printf("============================================\n");
		printf("=>         PEMESANAN TIKET BIOSKOP        <=\n");   // TAMPILAN UTAMA PROGRAM KITA
    	printf("============================================\n");
		printf("                                          ||\n");
		printf("Lanjutkan sebagai :                       ||\n");
		printf("                                          ||\n");
		printf("1. Pengunjung                             ||\n");
		printf("2. Admin                                  ||\n");
		printf("3. Keluar program                         ||\n");
		printf("                                          ||\n");
		printf("============================================\n\n");
		printf("Masukkan pilihan : ");
		scanf("%d", &p);
		
//=========================================================================================================================================================
	
		if (p==1){   // PANEL PENGUNJUNG
			int pil;
		
			do{
			system("cls");
			printf("============================================\n");
    		printf("=>            PANEL PENGUNJUNG            <=\n");
    		printf("============================================\n");
    		printf("                                          ||\n");
			printf("1. Pilih film                             ||\n");
			printf("2. Lihat kursi kosong                     ||\n");
			printf("3. Lihat denah tempat duduk               ||\n");
			printf("4. Keluar                                 ||\n");
			printf("                                          ||\n");
			printf("============================================\n\n");
			printf("Masukkan pilihan : ");
			scanf("%d", &pil);
			
			if (pil==1){   // INPUT DATA PENGUNJUNG - ENQUEUE
				system("cls");
				printf("===================================================\n");
				printf("=>                JADWAL  TAYANG                <=\n");   // TAMPILAN UTAMA PROGRAM KITA
    			printf("===================================================\n");
    			printf("                                                 ||\n");
				printf("   JUDUL FILM   ||  JAM  TAYANG  || HARGA  TIKET ||\n");
				printf("-------------------------------------------------||\n");
				printf("1. FORREST GUMP ||  09.00-11.00  || Rp 20.000,00 ||\n");
				printf("2. PAPER TOWN   ||  12.00-14.00  || Rp 25.000,00 ||\n");
				printf("3. VENOM        ||  15.00-17.00  || Rp 30.000,00 ||\n");
				printf("                                                 ||\n");
				printf("===================================================\n\n");
				printf("Film        : ");
				scanf("%d",&pilFilm);
				
				if(pilFilm==1)
					strcpy(film,"FORREST GUMP");
				else if(pilFilm==2)
					strcpy(film,"PAPER TOWN");
				else if(pilFilm==3)
					strcpy(film,"VENOM");
				else{
					printf("Film itu tidak ada!");
					getch(); system("cls");
					goto z;
				}
            
				printf("Nomor kursi : ");
            	scanf("%d",&num);
            	if(num<1 || num>30){
            		printf("hanya ada kursi 1-30!");
            		getch(); system("cls");
            		goto z;
				}
				node *temp = myQueue.front;
				while(temp != NULL){
					if(num == temp->data && strcmp(film,temp->film)==0){
						break;
					}
					temp=temp->next;
				}
				if(temp == NULL && cekcoy(root,num,film,1))
            		success=enqueue(num,film,&myQueue);
            	else{
            		printf("Sudah terpesan/masuk daftar antrian\nTidak dapat dipesan");
               		getch();
				}
            
				if(success==0){
            		printf("operasi enqueue gagal");
               		getch();
            	}
			}
	
			else if (pil==2){   // LIHAT KURSI KOSONG - TRANVERSE SINGLE LINKED LIST
				tranverse(head);
				getch();
			}
			
			else if (pil==3){   // LIHAT DENAH TEMPAT DUDUK
				system("cls");
				tampil();
				getch();
			}
	
			else if (pil>4 || pil<1){   // APABILA PENGUNJUNG MEMBERI MASUKKAN SELAIN 1-3
				printf("pilihan invalid!");
				getch();
			} system("cls");
			
			} while(pil!=4);   // KEMBALI KE TAMPILAN UTAMA PROGRAM
		}
		
//=========================================================================================================================================================		

		else if (p==2){   // PANEL ADMIN
			int pil;
			char name[6], pass[6];
			
			do{
			printf("\nusername : ");	scanf("%s", &name);
			printf("password : ");		scanf("%s", &pass);			
			
			if (strcmp("admin", name) == 0 && strcmp("admin", pass) == 0){   // PROSES AUTENTIKASI
				
				do{system("cls");
						
				printf("============================================\n");
    			printf("=>              PANEL ADMIN               <=\n");
    			printf("============================================\n");
    			printf("                                          ||\n");
				printf("1. Tampilkan antrian                      ||\n");
				printf("2. Verifikasi                             ||\n");
				printf("3. Tampilkan kursi                        ||\n");
				printf("4. Laporan hari ini                       ||\n");
				printf("5. Kembali ke menu utama                  ||\n");
				printf("                                          ||\n");
				printf("============================================\n\n");
				printf("Masukkan pilihan : ");
				scanf("%d", &pil);
				
				if (pil==1){   // TAMPILKAN ANTRIAN - SHOW QUEUE
					system("cls");
         			display(myQueue);
					getch();
				}
	
				else if (pil==2){   // HAPUS ANTRIAN - DEQUEUE
					dequeue(&myQueue,&root,&head);
					getch();
				}
	
				else if (pil==3){   // LIHAT KURSI KOSONG - SINGLE LINKED LIST
					tranverse(head);
					getch();
				}
	
				else if (pil==4){   // LIHAT LAPORAN - BINARY SEARCH TREE
					a=0; b=0; c=0;
					inorder(root, &a, &b, &c);
					
					if(a+b+c == 0){
						printf("Belum ada pemesanan!");
					}
	
					if(a+b+c != 0){
						printf("Laba dari film FORREST GUMP adalah : Rp %d\n", a);
						printf("Laba dari film PAPER TOWN adalah   : Rp %d\n", b);
						printf("Laba dari film VENOM adalah        : Rp %d\n", c);
						printf("Laba total                         : Rp %d", a+b+c);
					} getch();
				}
	
				else if (pil<1 || pil>5){   // APABILA PENGUNJUNG MEMBERI MASUKKAN SELAIN 1-6
					printf("Pilihan invalid!");
					getch();
					system("cls");
				}
				
				} while(pil!=5);   // KEMBALI KE TAMPILAN UTAMA PROGRAM
			}
		
			else{   // PROSES AUTENTIKASI GAGAL
				printf("nama pengguna dan kata sandi salah!");
				getch();	system("cls");	goto z;
			} system("cls");
			
			} while(pil!=5);   // KEMBALI KE TAMPILAN UTAMA PROGRAM
		}
		
		else if(p<1 || p>3){   // APABILA MEMBERI MASUKAN SELAIN 1 SAMPAI 3
			printf("pilihan invalid!");
			getch();
			system("cls");
		}
		
	} while(p!=3); destroy(&myQueue); deleteList(head); deleteBST(&root);   // KELUAR PROGRAM
}
