#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  long long int nrp;
  char nama[30], jeka, alamat[30];
  struct node *next;
};
typedef struct node node;

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

void tranverse(node *head);

node *createNode(void) { // BIKIN SINGLE LINKED LIST
  node *ptr;
  ptr = (node *)malloc(sizeof(node));
  return (ptr);
}

void insertNode(node **head, node *pPre, node *pNew) {
  if (pPre == NULL) {
    pNew->next = *head;
    *head = pNew;
  } else {
    pNew->next = pPre->next;
    pPre->next = pNew;
  }
}

void tambahAwal(node **head) { // PILIHAN KE 1 - MEMASUKKAN DATA
  node *pTemp;
  long long int nrp;
  char nama[30], jeka, alamat[30];
  printf("Masukkan NRP : ");
  if (!bacaAngka(&nrp, 1, LLONG_MAX))
    return;
  printf("Masukkan Nama : ");
  if (!bacaTeks(nama, sizeof(nama)))
    return;
  printf("Masukkan Jenis Kelamin (l/p) : ");
  if (!bacaPilihan(&jeka, "lpLP"))
    return;
  printf("Masukkan Alamat : ");
  if (!bacaTeks(alamat, sizeof(alamat)))
    return;
  pTemp = createNode();

  if (pTemp != NULL) {
    pTemp->nrp = nrp;
    strcpy(pTemp->nama, nama);
    pTemp->jeka = jeka;
    strcpy(pTemp->alamat, alamat);
    pTemp->next = NULL;
    insertNode(head, NULL, pTemp);
  } else {
    printf("Alokasi memori gagal");
  }
}

void updateData(node **head) { // PILIHAN NOMOR 2 - MEMPERBARUI DATA
  node *pTemp;
  long long int nrp;
  char nama[30], jeka, alamat[30];

  printf("Memperbarui data\n\n");
  printf("Masukkan NRP : ");
  if (!bacaAngka(&nrp, 1, LLONG_MAX))
    return;

  printf("Masukkan Nama : ");
  if (!bacaTeks(nama, sizeof(nama)))
    return;

  printf("Masukkan Jenis Kelamin (l/p) : ");
  if (!bacaPilihan(&jeka, "lpLP"))
    return;

  printf("Masukkan Alamat : ");
  if (!bacaTeks(alamat, sizeof(alamat)))
    return;

  pTemp = *head;
  while (pTemp != NULL && pTemp->nrp != nrp)
    pTemp = pTemp->next;

  if (pTemp != NULL) {
    pTemp->nrp = nrp;
    strcpy(pTemp->nama, nama);
    pTemp->jeka = jeka;
    strcpy(pTemp->alamat, alamat);
  } else
    printf("Data yang ingin dirubah  melalui NRP tidak ditemukan!");
}

void deleteNode(node **head, node *pPre, node *pCur) {
  if (pPre == NULL)
    *head = pCur->next;
  else
    pPre->next = pCur->next;
  free(pCur);
}

void hapusData(node **head) { // PILIHAN NOMOR 3 - MENGHAPUS DATA
  node *pCur, *pPre;
  long long int nrp;
  tranverse(*head);

  printf("\n\nData yang ingin dihapus?\nMasukkan NRP : ");
  if (!bacaAngka(&nrp, 1, LLONG_MAX))
    return;

  pPre = NULL;
  pCur = *head;

  while (pCur != NULL && pCur->nrp != nrp) {
    pPre = pCur;
    pCur = pCur->next;
  }

  if (pCur != NULL)
    deleteNode(head, pPre, pCur);
  else {
    printf("\nTidak ada data seperti itu!");
  }
}

void tranverse(node *head) { // PILIHAN KE 4 - MENAMPILKAN DATA
  node *pWalker;
  int i = 0;
  pWalker = head;

  if (pWalker == NULL)
    printf("NULL");

  while (pWalker != NULL) {
    printf("=-=-=-=-=-Data ke %d-=-=-=-=-=", i + 1);
    printf("\nNRP'nya       : %lli", pWalker->nrp);
    printf("\nNAMA'nya      : %s", pWalker->nama);
    printf("\nJenis Kelamin : %c", pWalker->jeka);
    printf("\nAlamat        : %s\n\n", pWalker->alamat);
    i++;
    pWalker = pWalker->next;
  }
}

void deleteList(
    node *head) { // APABILA KITA MEMBERI MASUKAN BERUPA "q" | KELUAR APLIKASI
  node *pTemp;

  while (head != NULL) {
    pTemp = head;
    head = head->next;
    free(pTemp);
  }
}

int main(void) { // PROGRAM UTAMA
  node *head;
  char pilih;
  head = NULL;

  do {
    printf("------- MENU DAFTAR HADIR MAHASISWA -------");
    printf("\n\n1. Tambah data");
    printf("\n2. Update data");
    printf("\n3. Delete data");
    printf("\n4. Tampilkan data");
    printf("\n\nMasukkan pilihan (tekan q untuk keluar) : ");
    if (!bacaPilihan(&pilih, "1234q"))
      break;

    if (pilih == '1')
      tambahAwal(&head);
    else if (pilih == '2')
      updateData(&head);
    else if (pilih == '3')
      hapusData(&head);
    else if (pilih == '4') {
      tranverse(head);
    }
  } while (pilih != 'q');
  deleteList(head);
  return 0;
}
