#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int data;
    struct node *next;
}; typedef struct node node;

struct stack{
    int count;
    node *top;
}; typedef struct stack stack;

stack createStack (void){ 
    stack head;
	head.count = 0;
	head.top = NULL;
	return(head);
}

int push (int data, stack *head){   // BUAT NAMBAH ELEMEN
   node *baru;int success;
   baru=(node *)malloc(sizeof(node));

   baru->data=data;
   baru->next=head->top;
   head->top=baru;
   head->count=(head->count)+1;
   
   success=1;
   return(success);
}

void pop (stack *head){   // BUAT MENGHAPUS ELEMEN YANG PALING ATAS
	node *pcur;

	pcur = head->top;
	head->top = pcur -> next;
	head->count = (head->count)-1;

	free(pcur);
}

void hacurKeluar(stack *head){   // MENGAHPUS SELURUH ELEMEN STACK LALU KELUAR PROGRAM
	node *ppre = head -> top,*pcur;

	while(ppre != NULL ){
		ppre = ppre -> next;
   		pcur = head->top;
		head->top = pcur -> next;
		head->count = (head->count)-1;
   		free(pcur);
   }
}

void display (stack head){   // BUAT NAMPILIN STACK
   system("cls");
   node *temp;
   temp = head.top;
   
   printf("stack element(s) from top to bottom : \n");
   printf("\n\t+---+ top");
   if(head.count==0)
         printf("\n\tNULL\n");
   else{
   	    while(temp){
		   printf("\n\t| %d |", temp->data);
		   temp = temp->next;
		}
   }
   printf("\n\t+---+ bottom");
   getch();
}

int main(void){   // PROGRAM UTAMA
  int choice, success,num,i,hasil;
  char code[] = "function showUsername(data[]) { echo 'username: '.data['user'];} ";
  stack head;
  head = createStack();

  while(1){
    system("cls");
    printf("-----COMPILER MENU-----\n");
    printf("\n1. show code");
    printf("\n2. compile code");
    printf("\n3. exit");
    printf("\n\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice){
    case 1:	printf("\n%s",code);
    		getch();
    break;

	case 2: printf("\nHASIL COMPILE : ");
	    int lencode =strlen(code);
            for(i=0; i<lencode; i++)
            {
                    if(code[i]=='(' || code[i]=='{' || code[i]=='[')
                        success = push(code[i], &head);
                    if(code[i]==')' || code[i]=='}' || code[i]==']'){
                    	if(head.count == 0)
                    		hasil = 0;
						else
    						pop(&head);
                    }
            }
			if(hasil ==0){
				printf("TIDAK VALID!");
				getch();
				break;
			}
			else{
				if(head.count != 0){
				printf("TIDAK VALID!");
				getch();	
			}
				else{
				printf("VALID!");
				getch();
				}
			}
    break;

	case 3:
		hacurKeluar(&head);
        exit(0);
    break;

    default: printf("\nInvalid Choice\n");// break;
    }
  }
}
