#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int data;
	char plat[10], tipe[10], merk[10];
   struct node *next;
}; typedef struct node node;

struct queue{
	int count;
   node *front;
   node *rear;
}; typedef struct queue queue;

queue createQueue(void) {
 queue myQueue;

 myQueue.count=0;
 myQueue.front=NULL;
 myQueue.rear=NULL;
 return(myQueue);
}

int enqueue(int data, char plat[10], char tipe[10], char merk[10],queue *myQueue){
int success;
 
	if(myQueue->count>=10)
 		success=0;
 	
	else{
  		node *newPtr;
  		newPtr=(node*)malloc(sizeof(node));
  
  		newPtr->data=data;
  		strcpy(newPtr->plat,plat);
  		strcpy(newPtr->tipe,tipe);
  		strcpy(newPtr->merk,merk);
		
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

node *createNode(void){
 node *newPtr;

 newPtr=(node *)malloc(sizeof(newPtr));
 return(newPtr);
}

void destroy(queue *myQueue){
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

void depan(queue myQueue){
 node *temp;

 temp=myQueue.front;
 printf("antrian mobil paling depan\n");
 
 printf("\n\n%4d\n",temp->data);
 printf("%4s\n",temp->plat);
 printf("%4s\n",temp->tipe);
 printf("%4s",temp->merk);
}

void belakang(queue myQueue){
 node *temp;

 temp=myQueue.rear;
 printf("antrian mobil paling belakang :\n");
 
 printf("\n\n%4d\n",temp->data);
 printf("%4s\n",temp->plat);
 printf("%4s\n",temp->tipe);
 printf("%4s",temp->merk);
}

void display(queue myQueue){
 node *temp;

 temp=myQueue.front;
 printf("elemen queue dari front ke rear :\n");
 while(temp){
  printf("\n\nNomor antrian     %d\n",temp->data);
  printf("Nomor plat        %s\n",temp->plat);
  printf("Tipe mobil        %s\n",temp->tipe);
  printf("Merk mobil        %s",temp->merk);
  temp=temp->next;
 }
}

void disbal(queue myQueue){
	node *temp;
	temp=myQueue.front;
	
	int n=0, c, d, a[100], b[100];
	
	while(temp){
		temp=temp->next;
		n++;
	}; 
	
	char x[n][11], z[n][11], y[n][11], plat[n][10], tipe[n][10], merk[n][10]; 
	temp=myQueue.front;
	for (c = 0; c < n; c++){
      b[c] = temp->data;
	  strcpy(x[c],temp->plat);
	  strcpy(y[c],temp->tipe);
	  strcpy(z[c],temp->merk);
      temp=temp->next;
  	}
 
   for (c = n-1, d = 0; c >= 0; c--, d++){
      a[d] = b[c];
      strcpy(plat[d],x[c]);
      strcpy(tipe[d],y[c]);
      strcpy(merk[d],z[c]);
	}
 
   printf("Antrian dari belakang ke depan\n\n");
 
   for (c = 0; c < n; c++){
    printf("Nomor antrian : %d\n", a[c]);
    printf("Plat mobil : %s\n", plat[c]);
    printf("Tipe mobil : %s\n", tipe[c]);
    printf("Merk mobil : %s\n\n", merk[c]);
	}
}

void dequeue(queue *myQueue){
 	 int dequeue;
	 if(myQueue->count==0) {
	 	printf("\nQueue is Empty!");
	 }
	 else{
	  node *dltPtr;
	  dltPtr = myQueue->front;
	  dequeue = dltPtr->data;
	  myQueue->front=myQueue->front->next;
	  free(dltPtr);
	  
	  myQueue->count--;
	  printf("\nnomor antrian yang selesai dicuci: %d",dequeue);
	 }
}

void duit(queue *myQueue){

 	float dequeue;
	if(myQueue->count==0) {
	 	printf("\nBelum untung boz!");
	 }
	 
	else{
	  node *dltPtr;
	  dltPtr = myQueue->front;
	  dequeue = dltPtr->data;
	  
	  printf("\nUntung hari in boz! : %2.f", ((dequeue*30000)-30000));
	}
}

int main(){
	int choice, num, success;
	char plat[10], tipe[10], merk[10];
   	queue myQueue;

   myQueue=createQueue();
   while(1){
   	system("cls");
    printf("\n-----QUEUE MENU-----\n");
    printf("\n1. Tambah Antrian");
    printf("\n2. Mobil Selesai dicuci");
    printf("\n3. Lihat antrian mobil");
    printf("\n4. Lihat antrian mobil dari belakang ke depan");
    printf("\n5. Lihat mobil depan");
    printf("\n6. Lihat mobil belakang");
	printf("\n7. Jumlah pemasukan");
	printf("\n8. Exit");
    printf("\n\nEnter your choice: ");
    scanf("%d",&choice);

    printf("\n\n");
    switch(choice){
      	case 1:
         	printf("Nomor antrian : ");
            scanf("%d",&num);
            printf("Nomor plat    : ");
            scanf("%s",&plat);
            printf("Tipe mobil    : ");
            scanf("%s",&tipe);
            printf("Merk mobil    : ");
            scanf("%s",&merk);
            
            success=enqueue(num,plat,tipe,merk,&myQueue);
            
			if(success==0){
            	printf("operasi enqueue gagal");
               	getch();
            }
            break;
         
		 case 2:
         	dequeue(&myQueue);
            getch();
            break;
         
		 case 3:
         	display(myQueue);
            getch();
            break;
         
         case 4:
         	disbal(myQueue);
            getch();
            break;
         
         case 5:
         	depan(myQueue);
            getch();
            break;
         
		 case 6:
         	belakang(myQueue);
            getch();
            break;   
         
         case 7:
         	duit(&myQueue);
            getch();
            break;
         
		 case 8:
         	destroy(&myQueue);
            exit(1);
         default:printf("\nInvalid Choice\n");break;
      }
   }
   
   return 0;
}
