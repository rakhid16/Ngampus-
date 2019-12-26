#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};	typedef struct node node;

struct stack{
    int count;
    node *top;
};	typedef struct stack stack;

node *createNode (void){
   node *newPtr;
   newPtr = (node *)malloc(sizeof(newPtr));
   return(newPtr);
}

stack createStack (void){
  stack head;
  head.count = 0;
  head.top = NULL;
  return(head);
}

int push (int data, stack *head){   // PILIHAN NOMOR 1
   node *baru;int success;
   baru=(node *)malloc(sizeof(node));

   baru->data=data;
   baru->next=head->top;
   head->top=baru;
   head->count=(head->count)+1;
   success=1;
   return(success);
}

int stackTop(stack head){   // PILIHAN NOMOR 2
	int atas;
	atas=head.top->data;
    return(atas);
}

void display (stack head){   // PILIHAN NOMOR 3
   system("cls");
   node *temp;
   temp = head.top;
   printf("stack element(s) from top to bottom : \n");

   printf("\n\t+---+ top");

	if(head.count==0){
		printf("\n\tNULL\n");
   }
   else{
   	     while(temp){
   	           printf("\n\t| %d |", temp->data);
   	           temp = temp->next;
   	     }
   }
   printf("\n\t+---+ bottom");
   getch();
}

void pop(stack *head){   // PILIHAN NOMOR 4
	
	node *pcur;
	
	pcur = head->top;
	head->top = pcur -> next;
	head->count = (head->count)-1;
	
	free(pcur);
}

void jumlahStack(stack head){   // PILIHAN NOMOR 5
	node *temp;
   	temp = head.top;
	
	system ("cls");
	int i=0;
	
	while (temp){
		temp = temp->next;
		i++;
	}
	printf("jumlah stack : %d", i);
}

void tambahStack(stack head){
	node *temp;
   	temp = head.top;
	
	system ("cls");
	int i=0, a=0;
	
	while (temp){
		a = a + temp -> data;
		temp = temp->next;
		i++;
	}
	
	printf("jumlah isi stack : %d", a);
}

void search(stack *head){   // PILIHAN NOMOR 6
	int key;
	
	printf("masukkan :");
	scanf("%d",&key);
	
	node *temp = head->top;
	
	while(temp != NULL){
		if(temp->data == key){
			printf("Key Found");
			return;
		}
		temp = temp->next;
	}
	printf("Key Not Found\n");
}

void deex(stack *head){   // PILIHAN NOMOR 7
	node *ppre = head -> top,*pcur;
	
	while(ppre != NULL ){

	ppre = ppre -> next;	
   	pcur = head->top;
	head->top = pcur -> next;

	head->count = (head->count)-1;
   		free(pcur);
   }
	display(*head);
	exit(0);
}

void cekStack(stack *head){ // PILIHAN NOMOR 9 & 10 
	node *temp = head->top;

	if(temp == NULL){
		printf("EMPTY");
	}
	else{
		printf("NOT EMPTY");
	}
}

int main(void){   // PROGRAM UTAMA
  int choice, num, success;
  stack head;
  head = createStack();

  while(1){
    system("cls");
    printf("\n-----STACK MENU-----\n");
    printf("\n1. Push element");
    printf("\n2. Element in top of stack");
    printf("\n3. Display Stack");
    printf("\n4. Pop element");
    printf("\n5. Number element of Stack");
    printf("\n6. Search an element");
    printf("\n7. Destroy Stack and EXIT");
    printf("\n8. Count all element of Stack");
    printf("\n9. is Stack empty or not?");
    printf("\n\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice){
    case 1:	printf("\nElement to be pushed: "); scanf("%d",&num);
        	success = push(num, &head);
         	if (success == 0){
         		printf("\nstack is FULL");
            	printf("\nTry again after you pop some elements");
            	getch();
            }
         	  break;

    case 2:	num = stackTop(head);
			printf("\nTop Element of Stack : %d ",num);
        	getch();
        	break;

    case 3:	display(head);
        	break;
         	  
    case 4:	pop(&head);
        	break;
    
    case 5: jumlahStack(head);	    
        	getch();
			break;
    
    case 6: search(&head);
    		getch();
    		break;
    
	case 7: deex(&head);
			getch();
			break;
		
	case 8: tambahStack(head);
			getch();
			break;
	
    case 9: cekStack(&head);
    		getch();
    		break;

    default: printf("\nInvalid Choice\n"); break; 
    }
  }
}
