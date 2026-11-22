# Proyek Akhir Mata Kuliah Sistem Digital

Kalkulator bilangan bulat dengan keluaran kode segmen a–g untuk setiap digit.
Pemetaan digit menggunakan tabel lookup; konversi angka O(jumlah digit), tanpa
alokasi dinamis. Segmen `g` dipakai sebagai tanda minus. Pembagian merupakan
pembagian bilangan bulat (dibulatkan menuju nol).

## Menjalankan

Dari root repositori dengan compiler C11:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic "Sistem Digital/KODE.c" -o /tmp/ngampus-bcd
/tmp/ngampus-bcd
```

Masukkan pilihan dan setiap operand pada baris terpisah. Operand menggunakan
rentang `long long`; input di luar rentang, karakter tambahan, dan baris terlalu
panjang ditolak. Penjumlahan, pengurangan, perkalian, serta pembagian diperiksa
sebelum operasi untuk mencegah overflow. Pembagian dengan nol ditolak. Angka nol,
negatif, dan `LLONG_MIN` dapat ditampilkan tanpa negasi yang overflow.

## Uji regresi

Membutuhkan Python 3 dan compiler C11, tanpa paket tambahan:

```sh
python3 "Sistem Digital/test_kode.py"
CC=clang CFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" python3 "Sistem Digital/test_kode.py"
```

Suite menguji aritmetika dengan batas integer 64-bit dan nilai acak deterministik,
pemetaan digit, input invalid, EOF, dan pemulihan setelah operasi ditolak. Build
menggunakan warning sebagai error. Binary/harness berada di direktori sementara
dan dibersihkan otomatis. `CC` dan `CFLAGS` dapat disesuaikan; sanitizer membutuhkan
compiler yang mendukungnya.

Terima kasih kepada Mohammad Idham Fachrurrozi atas kontribusinya.
