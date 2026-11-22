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
  int tingbad;
  char jeka, nama[30];
  struct node *next;
};
typedef struct node node;

node *pList = NULL;
static node *pLast = NULL;

node *alokasiNodeBaru(void) {
  node *pNew = NULL;
  pNew = (node *)malloc(sizeof(node));
  return (pNew);
}

void tambahAwal(node *pNew) {
  if (pNew == NULL)
    return;
  if (pList == NULL) {
    pNew->next = pNew;
    pLast = pNew;
  } else {
    pNew->next = pList;
    pLast->next = pNew;
  }
  pList = pNew;
}

void cetak(void) {
  node *pWalker;
  pWalker = pList;

  if (pWalker == NULL)
    printf("data kosong");

  else {
    printf("Data Mahasiswa yang Kemping\n\n");

    while (pWalker->next != pList) {
      printf("Nama   : %s", pWalker->nama);
      printf("\nGender : %c", pWalker->jeka);
      printf("\nTinggi : %d\n\n", pWalker->tingbad);
      pWalker = pWalker->next;
    }

    printf("Nama   : %s", pWalker->nama);
    printf("\nGender : %c", pWalker->jeka);
    printf("\nTinggi : %d\n\n", pWalker->tingbad);
  }
}

void hapusAwal(void) {
  node *pHapus = pList;
  if (pList == NULL)
    return;
  if (pList == pLast) {
    pList = NULL;
    pLast = NULL;
  } else {
    pList = pList->next;
    pLast->next = pList;
  }
  free(pHapus);
}

void hapusTengah(void) {
  if (pList == NULL) {
    printf("data kosong");
    return;
  }
  cetak();
  int zeke, co;
  printf("Sub menu :\n1. Hapus nama yang terakhir dimasukkan(nama paling "
         "atas)\n2. Hapus nama lain\n\nMasukkan pilihan : ");
  if (!bacaInt(&co, 1, 2))
    return;
  if (co == 1) {
    hapusAwal();
    return;
  }
  printf("Masukkan tinggi mahasiswa yang ingin dihapus/keluar circle : ");
  if (!bacaInt(&zeke, 1, INT_MAX))
    return;
  node *pCari = pList, *pPre = pLast;
  do {
    if (pCari->tingbad == zeke) {
      if (pCari == pList)
        hapusAwal();
      else {
        pPre->next = pCari->next;
        if (pCari == pLast)
          pLast = pPre;
        free(pCari);
      }
      return;
    }
    pPre = pCari;
    pCari = pCari->next;
  } while (pCari != pList);
  printf("Data tidak ditemukan!");
}

int main(void) {
  node *pNew;
  int pilih, tingbad;
  char nama[30], jeka;

  do {
    printf("Menu\n\n1. Tambah Data\n2. Hapus Data\n3. Tranverse\n4. Keluar "
           "Program\n\nMasukkan pilihan : ");
    if (!bacaInt(&pilih, 1, 4))
      break;

    if (pilih == 1) {
      printf("Masukkan nama          : ");
      if (!bacaTeks(nama, sizeof(nama)))
        break;

      printf("Masukkan jenis kelamin : ");
      if (!bacaPilihan(&jeka, "lpLP"))
        break;

      printf("Masukkan tinggi badan  : ");
      if (!bacaInt(&tingbad, 1, INT_MAX))
        break;

      pNew = alokasiNodeBaru();
      if (pNew == NULL) {
        printf("Alokasi memori gagal");
        continue;
      }

      pNew->tingbad = tingbad;
      strcpy(pNew->nama, nama);
      pNew->jeka = jeka;
      tambahAwal(pNew);
    }

    else if (pilih == 2)
      hapusTengah();

    else if (pilih == 3) {
      cetak();
    } else if (pilih != 4 && pilih != 2 && pilih != 1 && pilih != 3) {
      printf("Menu tersebut ndak ada");
    }

  } while (pilih != 4);

  while (pList != NULL)
    hapusAwal();
  return 0;
}
