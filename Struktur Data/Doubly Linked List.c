#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	long long int npm;
	char nama[30], jurusan[30];
	int semester;
	struct node *right;
    struct node *left;
}; typedef struct node node;

void tranverse(node *head);

node *createNode(void){   // BUAT NODE
  node *ptr;
  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}

void insertNode(node **head, node *pCur, node *pNew){   // BUAT NOMOR 2 & 3
	if(pCur != NULL){
		if(pCur->right == NULL){
			pNew->left = pCur;
			pNew->right = pCur->right;
			pCur->right = pNew;
		}	
		else{
			pNew->left = pCur;
			pNew->right = pCur->right;
			pCur->right->left = pNew;
			pCur->right = pNew;
		}
	}
}

void tambahAwal(node **head){   // PILIHAN NOMOR 1
	node *pTemp,*pCur;
	pCur = *head;
	
	long long int npm;
	char nama[30], jurusan[30];
	int semester;
	
	system("cls");
	
	printf("Masukkan NPM : ");
  	scanf("%lli", &npm);
  	fflush(stdin);
  
  	printf("Masukkan Nama : ");
  	scanf("%[^\n]%*c", &nama);
  	fflush(stdin);
  
  	printf("Masukkan Jurusan : ");
  	scanf("%[^\n]%*c", &jurusan);
  	fflush(stdin);
  	
  	printf("Masukkan Semester : ");
  	scanf("%i", &semester);
  	fflush(stdin);
	
	pTemp = (node *)malloc(sizeof(node));
	
	if(pCur == NULL){   // BUAT NAMBAH DATA PERTAMA KALI
		if(pTemp != NULL){
			
			pTemp->npm = npm;
  			strcpy(pTemp->nama,nama);
  			strcpy(pTemp->jurusan,jurusan);
  			pTemp->semester = semester;
    		
			pTemp->right = *head;
    		pTemp->left = NULL;
			*head = pTemp;
			
    		insertNode(head, NULL, pTemp);
		}	
		else{
		printf("Alokasi memori gagal");
        getch();
		}
	}
	
	else{   // BUAT NAMBAH DATA KE DUA DAN SETERUSNYA
		if(pTemp != NULL){
			
			pTemp->npm = npm;
  			strcpy(pTemp->nama,nama);
  			strcpy(pTemp->jurusan,jurusan);
  			pTemp->semester = semester;
			
			pTemp->right = *head;
			pTemp->left = NULL;
			pCur->left = pTemp;
			*head = pTemp;
		}
		else{
			printf("Alokasi memori gagal");
			getch();
		}
	}
}

void deleteNode(node **head, node *pCur ){   // BUAT NOMOR 5 & 6
	
	if(pCur == *head){
		if(pCur->left == pCur->right){
			*head = NULL;
		}
		else
		*head = pCur->right;
		pCur->left = NULL;
	}
	else if(pCur->right == NULL){
		pCur->left->right = NULL;
	}
	else{
		pCur->left->right = pCur->right;
		pCur->right->left = pCur->left;
	}
	free(pCur);
}

void hapusData(node **head){   // PILIHAN NOMOR 5
	long long int npm;
	node *pCur;
	pCur = *head;
	
	system("cls");
	
	if(pCur == NULL){
		system("cls");
		printf("Tidak ada data yang akan dihapus");
		getch();
	}
	else{
		tranverse(*head);
		printf("\nMasukkan NPM data yang akan dihapus : ");
		fflush(stdin);
		scanf("%lli",&npm);
	
		while(pCur != NULL && pCur->npm != npm){
			pCur = pCur->right;
		} deleteNode(head, pCur);

	system("cls");
	}
}

void updateData(node **head){   // PILIHAN NOMOR 2 - MEMPERBARUI DATA
	node *pTemp, *pCur;
	long long int npm;
	char nama[30], jurusan[30];
	int semester;
	
	system("cls");
	fflush(stdin);
	
	printf("Memperbarui data-Berdasarkan NPM\n\n");
	printf("Masukkan npm : ");
	scanf("%lli", &npm);
	fflush(stdin);
	
	printf("Masukkan Nama : ");
	scanf("%[^\n]%*c", &nama);
	fflush(stdin);
	
	printf("Masukkan jurusan : ");
	scanf("%[^\n]%*c", &jurusan);
	fflush(stdin);
	
	printf("Masukkan semester : ");
	scanf("%i", &semester);
	fflush(stdin);
	
	pTemp = *head;
	while(pTemp != NULL && pTemp -> npm != npm)
		pTemp = pTemp -> right;
	
	if(pTemp != NULL){
		pTemp->npm = npm;
		strcpy(pTemp->nama,nama);
		strcpy(pTemp->jurusan,jurusan);
		pTemp->semester = semester;
	}
	else
		printf("Data yang ingin dirubah  melalui npm tidak ditemukan!");
	getch();
}

void tranverse(node *head){   // PILIHAN NOMOR 7
    node *pWalker;
    int i=0;
    pWalker = head;
    
    system("cls");
    
	while(pWalker != NULL){
        printf("=-=-=-=-=-Data ke %d-=-=-=-=-=", i+1);
		printf("\nNPM'nya       : %lli", pWalker -> npm);
		printf("\nNAMA'nya      : %s", pWalker -> nama);
		printf("\nJurusan'nya   : %s", pWalker -> jurusan);
		printf("\nSemester      : %i\n\n", pWalker -> semester);
		i++;
        pWalker = pWalker->right;
    }
}

void lihatsmt(node *head){
	node *pWalker;
    int smt;
    system("cls");
    pWalker = head;
    
    printf("Melihat data berdasaran smt\n\n");
	printf("Masukkan semester : ");
	scanf("%i", &smt);
	fflush(stdin);
    
	while(pWalker != NULL && pWalker -> semester == smt){
		printf("\nNPM'nya       : %lli", pWalker -> npm);
		printf("\nNAMA'nya      : %s", pWalker -> nama);
		printf("\nJurusan'nya   : %s", pWalker -> jurusan);
		printf("\nSemester      : %i\n\n", pWalker -> semester);
        pWalker = pWalker->right;
    }
    pWalker = head;
}

void deleteList(node *head){   // KELUAR PROGRAM
  node *pTemp;

  while(head != NULL){
     pTemp = head;
     head = head->right;
     free(pTemp);
  }
}

int main(){   // PROGRAM UTAMA
	node *head;
	char pilih;
	head = NULL;
  
	do{
		system("cls");
		
		printf("------- Aplikasi Data Mahasiswa -------");
		printf("\n\n1. Tambah data");
		printf("\n2. Hapus data");
		printf("\n3. Update data");
		printf("\n4. Tampilkan data");
		printf("\n5. Tampilkan data Berdasarkan semester");
		printf("\n\nMasukkan pilihan (tekan q untuk keluar) : ");
		scanf("%c", &pilih);
		
		if (pilih == '1')
     		tambahAwal(&head);
		else if (pilih == '2')
			hapusData(&head);
		else if (pilih == '3')
     		updateData(&head);
		else if (pilih == '4'){
     		tranverse(head);
			getch();
		}
		else if (pilih == '5'){
     		lihatsmt(head);
     		getch();
     	}
	}while(pilih!='q');
	deleteList(head);
}
