#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	long long int nrp;
	char nama[30], jeka, alamat[30];
	struct node *next;
}; typedef struct node node;

void tranverse(node *head);

node *createNode(void){   // BIKIN SINGLE LINKED LIST
  node *ptr;
  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}

void insertNode(node **head, node *pPre, node *pNew){
    if (pPre == NULL){
	    pNew -> next = *head;
       *head = pNew;
    }
    else {
       pNew -> next = pPre -> next;
       pPre -> next = pNew;
   }
}

void tambahAwal(node **head){   // PILIHAN KE 1 - MEMASUKKAN DATA
  node *pTemp;
  long long int nrp;
  char nama[30], jeka, alamat[30];
  pTemp = (node *)malloc(sizeof(node));
  system("cls");
  fflush(stdin);
  
  printf("Masukkan NRP : ");
  scanf("%lli", &nrp);
  fflush(stdin);
  
  printf("Masukkan Nama : ");
  scanf("%[^\n]%*c", &nama);
  fflush(stdin);
  
  printf("Masukkan Jenis Kelamin (l/p) : ");
  scanf("%c", &jeka);
  fflush(stdin);
  
  printf("Masukkan Alamat : ");
  scanf("%[^\n]%*c", &alamat);
  fflush(stdin);

  if (pTemp != NULL){
  	pTemp->nrp = nrp;
  	strcpy(pTemp->nama,nama);
  	pTemp->jeka=jeka;
  	strcpy(pTemp->alamat,alamat);
    pTemp->next = NULL;
    insertNode(head, NULL, pTemp);
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

void updateData(node **head){   // PILIHAN NOMOR 2 - MEMPERBARUI DATA
	node *pTemp, *pCur;
	long long int nrp;
	char nama[30], jeka, alamat[30];
	system("cls");
	fflush(stdin);
	
	printf("Memperbarui data\n\n");
	printf("Masukkan NRP : ");
	scanf("%lli", &nrp);
	fflush(stdin);
	
	printf("Masukkan Nama : ");
	scanf("%[^\n]%*c", &nama);
	fflush(stdin);
	
	printf("Masukkan Jenis Kelamin (l/p) : ");
	scanf("%c", &jeka);
	fflush(stdin);
	
	printf("Masukkan Alamat : ");
	scanf("%[^\n]%*c", &alamat);
	fflush(stdin);
	
	pTemp = *head;
	while(pTemp != NULL && pTemp -> nrp != nrp)
		pTemp = pTemp -> next;
	
	if(pTemp != NULL){
		pTemp->nrp = nrp;
		strcpy(pTemp->nama,nama);
		pTemp->jeka = jeka;
		strcpy(pTemp->alamat,alamat);
		pTemp->next = NULL;
	}
	else
		printf("Data yang ingin dirubah  melalui NRP tidak ditemukan!");
	getch();
}

void deleteNode(node **head, node *pPre, node *pCur){
	if(pPre == NULL)
		*head = pCur -> next;
	else
		pPre->next = pCur->next;
	free(pCur);
}

void hapusData(node **head){   // PILIHAN NOMOR 3 - MENGHAPUS DATA
	node *pCur, *pPre;
	int pos;
	long long int nrp;
	system("cls");
	tranverse(*head);
	
	printf("\n\nData yang ingin dihapus?\nMasukkan NRP : ");
	scanf("%lli", &nrp);
	
	pPre = NULL;
	pCur = *head;
	
	while(pCur != NULL && pCur->nrp != nrp){
		pPre=pCur;
		pCur=pCur->next;
	}
	
	if(pCur!=NULL)
		deleteNode(head,pPre,pCur);
	else{
		printf("\nTidak ada data seperti itu!");
		getch();
	}
}

void tranverse(node *head){   // PILIHAN KE 4 - MENAMPILKAN DATA
	node *pWalker; int i=0;
	pWalker = head;
    system("cls");
	
	if(pWalker==NULL)
		printf("NULL");
	
	while(pWalker != NULL){
		printf("=-=-=-=-=-Data ke %d-=-=-=-=-=", i+1);
		printf("\nNRP'nya       : %lli", pWalker -> nrp);
		printf("\nNAMA'nya      : %s", pWalker -> nama);
		printf("\nJenis Kelamin : %c", pWalker -> jeka);
		printf("\nAlamat        : %s\n\n", pWalker -> alamat);
		i++;
		pWalker = pWalker -> next;
	}
}

void deleteList(node *head){   // APABILA KITA MEMBERI MASUKAN BERUPA "q" | KELUAR APLIKASI
  node *pTemp;

  while(head != NULL){
     pTemp = head;
     head = head->next;
     free(pTemp);
  }
}

int main(){   // PROGRAM UTAMA
	node *head;
	char pilih;
	head = NULL;
  
	do{
		system("cls");
		
		printf("------- MENU DAFTAR HADIR MAHASISWA -------");
		printf("\n\n1. Tambah data");
		printf("\n2. Update data");
		printf("\n3. Delete data");
		printf("\n4. Tampilkan data");
		printf("\n\nMasukkan pilihan (tekan q untuk keluar) : ");
		scanf("%c", &pilih);
		
		if (pilih == '1')
     		tambahAwal(&head);
		else if (pilih == '2')
			updateData(&head);
		else if (pilih == '3')
     		hapusData(&head);
		else if (pilih == '4'){
     		tranverse(head);
			getch();
		}
	}while(pilih!='q');
	deleteList(head);
}
