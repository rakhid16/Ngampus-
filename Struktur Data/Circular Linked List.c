#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct node{
	int tingbad;
	char jeka, nama[30];
    struct node *next;        
}; typedef struct node node;

node *pList = NULL;

node *alokasiNodeBaru(){ 
	node *pNew = NULL; 
	pNew = (node *) malloc(sizeof(node)); 
	return(pNew); 
}

void tambahAwal(node *pNew){
	node *temp;
	
	if(pList == NULL){
		pNew->next = pNew;
		pList = pNew;
	}
	
	else{
		temp = pList;
		
		while(temp->next != pList)
			temp = temp->next;
		
		temp->next = pNew;
		pNew->next = pList;
		pList = pNew;   
	}
}

void cetak(){
	node *pWalker;
	pWalker = pList;
	
	if(pWalker==NULL)
		printf("data kosong");
	
	else{
	printf("Data Mahasiswa yang Kemping\n\n");
	
	while(pWalker->next != pList){
		fflush(stdin);
		printf("Nama   : %s", pWalker->nama);
		printf("\nGender : %c", pWalker->jeka);
		printf("\nTinggi : %d\n\n", pWalker->tingbad);
		pWalker = pWalker->next;
	}fflush(stdin);
	
	printf("Nama   : %s", pWalker->nama);
	printf("\nGender : %c", pWalker->jeka);
	printf("\nTinggi : %d\n\n", pWalker->tingbad);
	}
}

void hapusAwal(){
    node *pEnd, *pHapus;
    pEnd=pList;
    pHapus=pList;
    
	while(pEnd->next!=pList)
		pEnd=pEnd->next;
    
	pEnd->next=pHapus->next;
    pList=pList->next;
    free(pHapus);
} 

void hapusTengah(){
	system("cls");
	
	if (pList==NULL){
		printf("data kosong");
		getch();
	}
	
	else{
		cetak();
		int zeke, co;
	
		printf("Sub menu :\n1. Hapus nama yang terakhir dimasukkan(nama paling atas)\n2. Hapus nama lain\n\nMasukkan pilihan : ");
		scanf("%d", &co);
	
		if (co==1)
			hapusAwal();
	
		else{
			printf("Masukkan tinggi mahasiswa yang ingin dihapus/keluar circle : "); scanf("%d",&zeke);
	
			node *pCari,*pPre;
			pPre=pList;
			pCari=pList;
	
			while(pCari->tingbad!=zeke)
				pCari=pCari->next;
	
			while(pPre->next!=pCari)
        		pPre=pPre->next;
	
			pPre->next=pCari->next;
			free(pCari);
		}
	}
}    
     
int main(int argc, char *argv[]){
	node *pNew;
	int pilih,tingbad;
	char nama[30], jeka;
	
	do{
		system("cls");
		
		printf("Menu\n\n1. Tambah Data\n2. Hapus Data\n3. Tranverse\n4. Keluar Program\n\nMasukkan pilihan : ");
		scanf("%d",&pilih);
    
    	if(pilih==1){
    		system("cls");
			pNew=alokasiNodeBaru();
			fflush(stdin);
			
			printf("Masukkan nama          : ");
			scanf("%[^\n]%*c",&nama);
			fflush(stdin);
			
			printf("Masukkan jenis kelamin : ");
			scanf("%c",&jeka);
			fflush(stdin);
			
			printf("Masukkan tinggi badan  : ");
			scanf("%d",&tingbad);
			fflush(stdin);
			
			pNew->tingbad=tingbad;
			strcpy(pNew->nama,nama);
			pNew->jeka=jeka;
			tambahAwal(pNew); 
        }
    
		else if(pilih==2)
			hapusTengah();
    	
		else if(pilih==3){
			system("cls");
			cetak();
			getch();
		}
		else if(pilih!=4 && pilih !=2 && pilih!=1 && pilih!=3){
			printf("Menu tersebut ndak ada");
			getch();
		}
                                
	}while(pilih!=4);  

	return 0;
}
