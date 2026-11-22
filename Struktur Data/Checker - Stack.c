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

int push(int data, stack *head) {
  node *baru = malloc(sizeof(*baru));
  if (baru == NULL)
    return 0;

  baru->data = data;
  baru->next = head->top;
  head->top = baru;
  head->count++;
  return 1;
}

int pop(stack *head, int *value) {
  node *top = head->top;
  if (top == NULL)
    return 0;
  *value = top->data;
  head->top = top->next;
  head->count--;
  free(top);
  return 1;
}

void destroyStack(stack *head) {
  int value;
  while (pop(head, &value)) {
  }
}

int isOpeningBracket(char value) {
  return value == '(' || value == '{' || value == '[';
}

int bracketsMatch(char opening, char closing) {
  return (opening == '(' && closing == ')') ||
         (opening == '{' && closing == '}') ||
         (opening == '[' && closing == ']');
}

/* 1: balanced, 0: mismatched brackets, -1: allocation failure. */
int isBalanced(const char *source) {
  stack brackets = createStack();
  int opening;

  for (const char *current = source; *current != '\0'; current++) {
    if (isOpeningBracket(*current)) {
      if (!push(*current, &brackets)) {
        destroyStack(&brackets);
        return -1;
      }
    } else if (*current == ')' || *current == '}' || *current == ']') {
      if (!pop(&brackets, &opening) ||
          !bracketsMatch((char)opening, *current)) {
        destroyStack(&brackets);
        return 0;
      }
    }
  }

  int balanced = brackets.count == 0;
  destroyStack(&brackets);
  return balanced;
}

void display(stack head) {
  node *temp;
  temp = head.top;

  printf("stack element(s) from top to bottom : \n");
  printf("\n\t+---+ top");
  if (head.count == 0)
    printf("\n\tNULL\n");
  else {
    while (temp) {
      printf("\n\t| %d |", temp->data);
      temp = temp->next;
    }
  }
  printf("\n\t+---+ bottom\n");
}

int main(void) { // PROGRAM UTAMA
  int choice;
  const char code[] =
      "function showUsername(data[]) { echo 'username: '.data['user'];} ";

  while (1) {
    printf("\n-----COMPILER MENU-----\n");
    printf("\n1. show code");
    printf("\n2. compile code");
    printf("\n3. exit");
    printf("\n\nEnter your choice: ");
    if (!readInt(&choice))
      return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;

    switch (choice) {
    case 1:
      printf("\n%s\n", code);
      break;

    case 2: {
      int result = isBalanced(code);
      if (result < 0)
        fputs("Alokasi memori gagal; pemeriksaan dibatalkan.\n", stderr);
      else {
        printf("\nHASIL COMPILE : ");
        puts(result ? "VALID!" : "TIDAK VALID!");
      }
      break;
    }

    case 3:
      return 0;

    default:
      printf("\nInvalid Choice\n"); // break;
    }
  }
}
