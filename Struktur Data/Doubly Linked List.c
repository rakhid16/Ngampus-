#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int bacaTeks(char *teks, size_t ukuran) {
  for (;;) {
    if (fgets(teks, (int)ukuran, stdin) == NULL)
      return 0;
    size_t panjang = strlen(teks);
    if (panjang > 0 && teks[panjang - 1] == '\n')
      teks[--panjang] = '\0';
    else {
      int c = getchar();
      if (c == '\r')
        c = getchar();
      if (c != '\n' && c != EOF) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        printf("Input terlalu panjang. Ulangi : ");
        continue;
      }
    }
    if (panjang > 0 && teks[panjang - 1] == '\r')
      teks[--panjang] = '\0';
    size_t i = 0;
    while (isspace((unsigned char)teks[i]))
      i++;
    if (teks[i] != '\0')
      return 1;
    printf("Input tidak boleh kosong. Ulangi : ");
  }
}

static int bacaAngka(long long int *nilai, long long int minimum,
                     long long int maksimum) {
  char teks[128], *akhir;
  while (bacaTeks(teks, sizeof(teks))) {
    errno = 0;
    long long int angka = strtoll(teks, &akhir, 10);
    if (akhir != teks && errno != ERANGE) {
      while (isspace((unsigned char)*akhir))
        akhir++;
      if (*akhir == '\0' && angka >= minimum && angka <= maksimum) {
        *nilai = angka;
        return 1;
      }
    }
    printf("Angka tidak valid. Ulangi : ");
  }
  return 0;
}

static int bacaPilihan(char *pilih, const char *pilihan) {
  char teks[32];
  while (bacaTeks(teks, sizeof(teks))) {
    if (teks[1] == '\0' && strchr(pilihan, teks[0]) != NULL) {
      *pilih = teks[0];
      return 1;
    }
    printf("Pilihan tidak valid. Ulangi : ");
  }
  return 0;
}

static int bacaInt(int *nilai, int minimum, int maksimum) {
  long long int angka;
  if (!bacaAngka(&angka, minimum, maksimum))
    return 0;
  *nilai = (int)angka;
  return 1;
}

struct node {
  long long int npm;
  char nama[30], jurusan[30];
  int semester;
  struct node *right;
  struct node *left;
};
typedef struct node node;

void tranverse(node *head);

node *createNode(void) { // BUAT NODE
  node *ptr;
  ptr = (node *)malloc(sizeof(node));
  return (ptr);
}

void insertNode(node **head, node *pCur, node *pNew) {
  pNew->left = pCur;
  pNew->right = pCur == NULL ? *head : pCur->right;
  if (pNew->right != NULL)
    pNew->right->left = pNew;
  if (pCur == NULL)
    *head = pNew;
  else
    pCur->right = pNew;
}

void tambahAwal(node **head) { // PILIHAN NOMOR 1
  node *pTemp;
  long long int npm;
  char nama[30], jurusan[30];
  int semester;

  printf("Masukkan NPM : ");
  if (!bacaAngka(&npm, 1, LLONG_MAX))
    return;
  printf("Masukkan Nama : ");
  if (!bacaTeks(nama, sizeof(nama)))
    return;
  printf("Masukkan Jurusan : ");
  if (!bacaTeks(jurusan, sizeof(jurusan)))
    return;
  printf("Masukkan Semester : ");
  if (!bacaInt(&semester, 1, INT_MAX))
    return;

  pTemp = createNode();
  if (pTemp == NULL) {
    printf("Alokasi memori gagal");
    return;
  }
  pTemp->npm = npm;
  strcpy(pTemp->nama, nama);
  strcpy(pTemp->jurusan, jurusan);
  pTemp->semester = semester;
  insertNode(head, NULL, pTemp);
}

void deleteNode(node **head, node *pCur) {
  if (pCur == NULL)
    return;
  if (pCur->left == NULL)
    *head = pCur->right;
  else
    pCur->left->right = pCur->right;
  if (pCur->right != NULL)
    pCur->right->left = pCur->left;
  free(pCur);
}

void hapusData(node **head) { // PILIHAN NOMOR 5
  long long int npm;
  node *pCur;
  pCur = *head;

  if (pCur == NULL) {
    printf("Tidak ada data yang akan dihapus");
  } else {
    tranverse(*head);
    printf("\nMasukkan NPM data yang akan dihapus : ");
    if (!bacaAngka(&npm, 1, LLONG_MAX))
      return;

    while (pCur != NULL && pCur->npm != npm) {
      pCur = pCur->right;
    }
    if (pCur != NULL)
      deleteNode(head, pCur);
    else
      printf("Data tidak ditemukan!");

  }
}

void updateData(node **head) { // PILIHAN NOMOR 2 - MEMPERBARUI DATA
  node *pTemp;
  long long int npm;
  char nama[30], jurusan[30];
  int semester;

  printf("Memperbarui data-Berdasarkan NPM\n\n");
  printf("Masukkan npm : ");
  if (!bacaAngka(&npm, 1, LLONG_MAX))
    return;

  printf("Masukkan Nama : ");
  if (!bacaTeks(nama, sizeof(nama)))
    return;

  printf("Masukkan jurusan : ");
  if (!bacaTeks(jurusan, sizeof(jurusan)))
    return;

  printf("Masukkan semester : ");
  if (!bacaInt(&semester, 1, INT_MAX))
    return;

  pTemp = *head;
  while (pTemp != NULL && pTemp->npm != npm)
    pTemp = pTemp->right;

  if (pTemp != NULL) {
    pTemp->npm = npm;
    strcpy(pTemp->nama, nama);
    strcpy(pTemp->jurusan, jurusan);
    pTemp->semester = semester;
  } else
    printf("Data yang ingin dirubah  melalui npm tidak ditemukan!");
}

void tranverse(node *head) { // PILIHAN NOMOR 7
  node *pWalker;
  int i = 0;
  pWalker = head;

  while (pWalker != NULL) {
    printf("=-=-=-=-=-Data ke %d-=-=-=-=-=", i + 1);
    printf("\nNPM'nya       : %lli", pWalker->npm);
    printf("\nNAMA'nya      : %s", pWalker->nama);
    printf("\nJurusan'nya   : %s", pWalker->jurusan);
    printf("\nSemester      : %i\n\n", pWalker->semester);
    i++;
    pWalker = pWalker->right;
  }
}

void lihatsmt(node *head) {
  node *pWalker;
  int smt;
  pWalker = head;

  printf("Melihat data berdasaran smt\n\n");
  printf("Masukkan semester : ");
  if (!bacaInt(&smt, 1, INT_MAX))
    return;

  while (pWalker != NULL) {
    if (pWalker->semester == smt) {
      printf("\nNPM'nya       : %lli", pWalker->npm);
      printf("\nNAMA'nya      : %s", pWalker->nama);
      printf("\nJurusan'nya   : %s", pWalker->jurusan);
      printf("\nSemester      : %i\n\n", pWalker->semester);
    }
    pWalker = pWalker->right;
  }
}

void deleteList(node *head) { // KELUAR PROGRAM
  node *pTemp;

  while (head != NULL) {
    pTemp = head;
    head = head->right;
    free(pTemp);
  }
}

int main(void) { // PROGRAM UTAMA
  node *head;
  char pilih;
  head = NULL;

  do {
    printf("------- Aplikasi Data Mahasiswa -------");
    printf("\n\n1. Tambah data");
    printf("\n2. Hapus data");
    printf("\n3. Update data");
    printf("\n4. Tampilkan data");
    printf("\n5. Tampilkan data Berdasarkan semester");
    printf("\n\nMasukkan pilihan (tekan q untuk keluar) : ");
    if (!bacaPilihan(&pilih, "12345q"))
      break;

    if (pilih == '1')
      tambahAwal(&head);
    else if (pilih == '2')
      hapusData(&head);
    else if (pilih == '3')
      updateData(&head);
    else if (pilih == '4') {
      tranverse(head);
    } else if (pilih == '5') {
      lihatsmt(head);
    }
  } while (pilih != 'q');
  deleteList(head);
  return 0;
}
