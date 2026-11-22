#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Consume the entire line, including any excess, before the next prompt. */
static int readLine(char *line, int capacity) {
  if (fgets(line, capacity, stdin) == NULL)
    return 0;

  char *newline = strchr(line, '\n');
  if (newline != NULL) {
    *newline = '\0';
  } else {
    int ch = getchar();
    if (ch != '\n' && ch != EOF) {
      while ((ch = getchar()) != '\n' && ch != EOF) {
      }
      puts("Input terlalu panjang. Ulangi:");
      return ferror(stdin) ? 0 : -1;
    }
  }
  return ferror(stdin) ? 0 : 1;
}

static int readInt(int *value) {
  char line[128];
  int status;

  while ((status = readLine(line, sizeof(line))) != 0) {
    if (status < 0)
      continue;
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

static int readText(char value[10]) {
  int status;
  while ((status = readLine(value, 10)) != 0) {
    if (status < 0)
      continue;
    for (const char *current = value; *current != '\0'; current++) {
      if (!isspace((unsigned char)*current))
        return 1;
    }
    puts("Input tidak boleh kosong. Ulangi:");
  }
  return 0;
}

struct node {
  int data;
  char plat[10], tipe[10], merk[10];
  struct node *next;
};
typedef struct node node;

struct queue {
  int count;
  unsigned long long completed;
  node *front;
  node *rear;
};
typedef struct queue queue;

queue createQueue(void) {
  queue myQueue;

  myQueue.count = 0;
  myQueue.completed = 0;
  myQueue.front = NULL;
  myQueue.rear = NULL;
  return (myQueue);
}

int enqueue(int data, const char *plat, const char *tipe, const char *merk,
            queue *myQueue) {
  if (myQueue->count >= 10)
    return 0;

  node *newPtr = malloc(sizeof(*newPtr));
  if (newPtr == NULL)
    return 0;

  newPtr->data = data;
  snprintf(newPtr->plat, sizeof(newPtr->plat), "%s", plat);
  snprintf(newPtr->tipe, sizeof(newPtr->tipe), "%s", tipe);
  snprintf(newPtr->merk, sizeof(newPtr->merk), "%s", merk);
  newPtr->next = NULL;

  if (myQueue->rear == NULL)
    myQueue->front = newPtr;
  else
    myQueue->rear->next = newPtr;

  myQueue->rear = newPtr;
  myQueue->count++;
  return 1;
}

void destroy(queue *myQueue) {
  while (myQueue->front != NULL) {
    node *temp = myQueue->front;
    myQueue->front = temp->next;
    free(temp);
  }

  myQueue->count = 0;
  myQueue->rear = NULL;
}

void depan(queue myQueue) {
  node *temp = myQueue.front;
  if (temp == NULL) {
    puts("Antrian kosong.");
    return;
  }
  printf("antrian mobil paling depan\n");

  printf("\n\n%4d\n", temp->data);
  printf("%4s\n", temp->plat);
  printf("%4s\n", temp->tipe);
  printf("%4s", temp->merk);
}

void belakang(queue myQueue) {
  node *temp = myQueue.rear;
  if (temp == NULL) {
    puts("Antrian kosong.");
    return;
  }
  printf("antrian mobil paling belakang :\n");

  printf("\n\n%4d\n", temp->data);
  printf("%4s\n", temp->plat);
  printf("%4s\n", temp->tipe);
  printf("%4s", temp->merk);
}

void display(queue myQueue) {
  node *temp;

  temp = myQueue.front;
  printf("elemen queue dari front ke rear :\n");
  while (temp) {
    printf("\n\nNomor antrian     %d\n", temp->data);
    printf("Nomor plat        %s\n", temp->plat);
    printf("Tipe mobil        %s\n", temp->tipe);
    printf("Merk mobil        %s", temp->merk);
    temp = temp->next;
  }
}

void cetakMundur(node *current) {
  if (current == NULL)
    return;

  cetakMundur(current->next);
  printf("Nomor antrian : %d\n", current->data);
  printf("Plat mobil : %s\n", current->plat);
  printf("Tipe mobil : %s\n", current->tipe);
  printf("Merk mobil : %s\n\n", current->merk);
}

void disbal(queue myQueue) {
  if (myQueue.front == NULL) {
    puts("Antrian kosong.");
    return;
  }

  printf("Antrian dari belakang ke depan\n\n");
  cetakMundur(myQueue.front);
}

int dequeue(queue *myQueue) {
  if (myQueue->front == NULL) {
    puts("\nQueue is Empty!");
    return 0;
  }
  if (myQueue->completed == ULLONG_MAX / 30000ULL) {
    puts("Pemasukan di luar rentang bilangan; antrian tidak diubah.");
    return 0;
  }

  node *dltPtr = myQueue->front;
  int number = dltPtr->data;
  myQueue->front = dltPtr->next;
  if (myQueue->rear == dltPtr)
    myQueue->rear = NULL;
  free(dltPtr);

  myQueue->count--;
  myQueue->completed++;
  printf("\nnomor antrian yang selesai dicuci: %d\n", number);
  return 1;
}

void duit(const queue *myQueue) {
  if (myQueue->completed == 0)
    puts("\nBelum untung boz!");
  else
    printf("\nUntung hari in boz! : %llu\n", myQueue->completed * 30000ULL);
}

int main(void) {
  int choice, num, success;
  char plat[10], tipe[10], merk[10];
  queue myQueue;

  myQueue = createQueue();
  while (1) {
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
    if (!readInt(&choice))
      break;

    printf("\n\n");
    switch (choice) {
    case 1:
      printf("Nomor antrian : ");
      if (!readInt(&num))
        goto cleanup;
      printf("Nomor plat    : ");
      if (!readText(plat))
        goto cleanup;
      printf("Tipe mobil    : ");
      if (!readText(tipe))
        goto cleanup;
      printf("Merk mobil    : ");
      if (!readText(merk))
        goto cleanup;

      success = enqueue(num, plat, tipe, merk, &myQueue);

      if (success == 0) {
        printf("operasi enqueue gagal\n");
      }
      break;

    case 2:
      dequeue(&myQueue);
      break;

    case 3:
      display(myQueue);
      break;

    case 4:
      disbal(myQueue);
      break;

    case 5:
      depan(myQueue);
      break;

    case 6:
      belakang(myQueue);
      break;

    case 7:
      duit(&myQueue);
      break;

    case 8:
      goto cleanup;
    default:
      printf("\nInvalid Choice\n");
      break;
    }
  }

cleanup:
  destroy(&myQueue);
  return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
}
