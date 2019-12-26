# IMPOR MODUL
from simpleeval import simple_eval
import pandas as pd
import math

# BERI MASUKKAN
persamaan = input("f(x): ")
n = float(input("\nBanyak irisan\t: "))
b = float(input("Batas atas (b)\t: "))
a = float(input("Batas bawah (a)\t: "))
batas_error = float(input("Galat\t\t: "))

# PERSIAPAN BUAT DATA-FRAME
c = [a]
h = (b - a) / n
while (c[-1] < 1):
    c.append(c[-1] + h)
c[-1] = b

# INISIALISASI VARIABEL
error = 0
hasil_asli = 0
iterasi = 0
nilx = [a]

# PROSES ITERASI
while True:
    h = (b - a) / n
    fa = simple_eval(persamaan, names={"x":a, "e":math.exp(1)})
    fb = simple_eval(persamaan, names={"x":b, "e":math.exp(1)})
    hasil =  fa + fb
    sigma = 0.0
    x = a

    i = 1
    while i < int(n):
        x += h
        nilx.append(x)   # Menambahkan nilai x pada list nilx
        sigma += (2.0 * simple_eval(persamaan, names={"x":x, "e":math.exp(1)}))
        i += 1
        
    hasil = (hasil + sigma) * h / 2.0
    
    # Catat hasil aslinya
    if iterasi == 0:
        hasil_asli = hasil

    # Cek error
    error = abs(hasil - error)
    if error <= batas_error:
        break
    
    error = hasil
    n *= 10     # Tambahkan segmen
    iterasi += 1

presentase_error = abs((hasil - hasil_asli) / hasil) * 100

# PERSIAPAN BUAT DATA-FRAME (2)
kolx = []
kolfx = []

w = 0
for q in range(len(nilx)):
    if c[w] == nilx[q]:
        kolx.append(nilx[q])
        w += 1
        
if (kolx[-1] >= 1.0 or kolx[-1] >= 1):
    kolx[-1] = b
else:
    kolx.append(b)

for item in range(len(kolx)):
    kolfx.append(2.0 * simple_eval(persamaan, names={"x":kolx[item], "e":math.exp(1)}))
    kolfx[item] = kolfx[item] / 2

# CETAK DATA-FRAME
raw_data = {'x': kolx, 'f(x)': kolfx}
df = pd.DataFrame(raw_data)
print("\nProses iterasi: ")
print(df)

# CETAK HASIL ITERASI DAN GALAT
print("\nNilai integrasinya numeriknya\t: %.8f" % hasil_asli)
print("Nilai integrasi paling akurat\t: %.8f" % hasil)
print("Error\t\t\t\t: %.3f persen" % presentase_error)
