# Struktur Data

Kumpulan implementasi struktur data dan proyek akhir. Setiap berkas `.c`
merupakan program mandiri dengan fungsi `main` masing-masing.

## Menjalankan

Dari root repositori, gunakan compiler C11 (Clang atau GCC), misalnya:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic "Struktur Data/Stack.c" -o /tmp/ngampus-stack
/tmp/ngampus-stack
```

Masukkan satu isian per baris. Nama/alamat dapat mengandung spasi sesuai batas
buffer program. Input tidak valid diminta ulang; EOF mengakhiri program dan
membebaskan memori. Program tidak lagi membutuhkan `conio.h`, perintah `cls`,
atau jeda satu tombol, sehingga keluaran juga bisa diuji melalui pipe.

## Perbaikan utama

- Stack: push/pop/peek tetap O(1); penjumlahan memakai `long long` dengan
  pemeriksaan overflow.
- Circular linked list: pointer tail membuat tambah/hapus awal O(1), termasuk
  kondisi kosong dan satu node. Pencarian tetap O(n).
- Single/doubly linked list: update dan penghapusan menjaga sambungan node;
  filter semester memeriksa seluruh list.
- Queue cuci mobil: enqueue/dequeue O(1), kapasitas 10 mobil; pemasukan dihitung
  dari jumlah mobil selesai × Rp30.000, bukan nomor antrian. Kolom teks maksimal
  9 karakter.
- Checker: pemeriksaan pasangan bracket O(n), memori O(kedalaman bracket).
  Ini bukan parser bahasa; bracket dalam string/komentar tetap ikut diperiksa.
- Proyek bioskop: alokasi node, pemetaan 90 kursi, verifikasi antrian, dan
  penghapusan BST diperbaiki; seluruh struktur dibersihkan saat keluar.

## Uji regresi

Membutuhkan Python 3 dan compiler C11, tanpa paket tambahan:

```sh
python3 "Struktur Data/test_programs.py"
```

Suite mengompilasi ketujuh program dengan warning sebagai error dan menguji
operasi normal, list kosong, EOF, pointer regression, bracket bertingkat, serta
pemesanan seluruh kursi. Binary dibuat di direktori sementara dan dibersihkan
otomatis. Compiler bisa dipilih melalui `CC`; flag tambahan melalui `CFLAGS`.
Untuk AddressSanitizer dan UndefinedBehaviorSanitizer pada compiler pendukung:

```sh
CC=clang CFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" python3 "Struktur Data/test_programs.py"
```

Terima kasih kepada Amir Fanani, Hanna Masfuva D., Annisa Fadhilasari, dan
Fajar Andhika atas kontribusinya pada proyek akhir.
