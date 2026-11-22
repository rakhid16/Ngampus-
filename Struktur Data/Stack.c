#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int readInt(int *value) {
  char line[128];

  while (fgets(line, sizeof(line), stdin) != NULL) {
    if (strchr(line, '\n') == NULL) {
      int ch = getchar();
      if (ch != '\n' && ch != EOF) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        puts("Input terlalu panjang. Masukkan bilangan bulat:");
        continue;
      }
    }
    if (ferror(stdin))
      return 0;

    char *end;
    errno = 0;
    long parsed = strtol(line, &end, 10);
    if (end != line && errno != ERANGE && parsed >= INT_MIN &&
        parsed <= INT_MAX) {
      while (isspace((unsigned char)*end))
        end++;
      if (*end == '\0') {
        *value = (int)parsed;
        return 1;
      }
    }
    puts("Input tidak valid. Masukkan bilangan bulat:");
  }
  return 0;
}

struct node {
  int data;
  struct node *next;
};
typedef struct node node;

struct stack {
  size_t count;
  node *top;
};
typedef struct stack stack;

stack createStack(void) {
  stack head;
  head.count = 0;
  head.top = NULL;
  return (head);
}

int push(int data, stack *head) { // PILIHAN NOMOR 1
  node *baru = malloc(sizeof(*baru));
  if (baru == NULL)
    return 0;

  baru->data = data;
  baru->next = head->top;
  head->top = baru;
  head->count++;
  return 1;
}

int stackTop(const stack *head, int *value) { // PILIHAN NOMOR 2
  if (head->top == NULL)
    return 0;
  *value = head->top->data;
  return 1;
}

void display(stack head) { // PILIHAN NOMOR 3
  node *temp;
  temp = head.top;
  printf("stack element(s) from top to bottom : \n");

  printf("\n\t+---+ top");

  if (head.count == 0) {
    printf("\n\tNULL\n");
  } else {
    while (temp) {
      printf("\n\t| %d |", temp->data);
      temp = temp->next;
    }
  }
  printf("\n\t+---+ bottom\n");
}

int pop(stack *head) { // PILIHAN NOMOR 4
  node *top = head->top;
  if (top == NULL)
    return 0;
  head->top = top->next;
  head->count--;
  free(top);
  return 1;
}

void jumlahStack(stack head) { // PILIHAN NOMOR 5
  printf("jumlah stack : %zu\n", head.count);
}

void tambahStack(stack head) {
  node *temp;
  temp = head.top;

  long long total = 0;

  while (temp) {
    if ((temp->data > 0 && total > LLONG_MAX - temp->data) ||
        (temp->data < 0 && total < LLONG_MIN - temp->data)) {
      puts("Jumlah isi stack di luar rentang bilangan.");
      return;
    }
    total += temp->data;
    temp = temp->next;
  }

  printf("jumlah isi stack : %lld\n", total);
}

int search(const stack *head) { // PILIHAN NOMOR 6
  int key;

  printf("masukkan :");
  if (!readInt(&key))
    return 0;

  node *temp = head->top;

  while (temp != NULL) {
    if (temp->data == key) {
      puts("Key Found");
      return 1;
    }
    temp = temp->next;
  }
  printf("Key Not Found\n");
  return 1;
}

void deex(stack *head) { // PILIHAN NOMOR 7
  while (pop(head)) {
  }
  printf("Stack berhasil dihapus.\n");
}

void cekStack(stack *head) { // PILIHAN NOMOR 9 & 10
  if (head->top == NULL) {
    printf("EMPTY");
  } else {
    printf("NOT EMPTY");
  }
}

int main(void) { // PROGRAM UTAMA
  int choice, num, value;
  stack head;
  head = createStack();

  while (1) {
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
    if (!readInt(&choice))
      break;

    switch (choice) {
    case 1:
      printf("\nElement to be pushed: ");
      if (!readInt(&num))
        goto cleanup;
      if (!push(num, &head)) {
        printf("\nAlokasi memori gagal.\n");
      }
      break;

    case 2:
      if (stackTop(&head, &value))
        printf("\nTop Element of Stack : %d ", value);
      else
        printf("\nStack is empty.\n");
      break;

    case 3:
      display(head);
      break;

    case 4:
      if (!pop(&head))
        printf("\nStack is empty.\n");
      break;

    case 5:
      jumlahStack(head);
      break;

    case 6:
      if (!search(&head))
        goto cleanup;
      break;

    case 7:
      goto cleanup;

    case 8:
      tambahStack(head);
      break;

    case 9:
      cekStack(&head);
      break;

    default:
      printf("\nInvalid Choice\n");
      break;
    }
  }

cleanup:
  deex(&head);
  return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
}
