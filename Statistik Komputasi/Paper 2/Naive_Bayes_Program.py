# Impor pustaka
import pandas as pd

# Fungsi pendukung menu
from numpy import array, arange, any
import subprocess as sp


# Baca data latih
data = pd.read_csv("monk.csv")

# Letakkan kolom kelas di posisi terakhir
kolom = data.pop("class")
data["class"] = kolom

# Hitung frekuensi setiap nilai atribut untuk tiap kelas
model = []
for i in range(len(data.columns) - 1):
    model.append([])
    ikr = 0
    for j in sorted(data[data.columns[i]].unique()):
        model[i].append([])
        model[i][ikr].append(
            len(
                data[data[data.columns[i]] == j][
                    data[data[data.columns[i]] == j]["class"] == 0
                ]
            )
        )
        model[i][ikr].append(
            len(
                data[data[data.columns[i]] == j][
                    data[data[data.columns[i]] == j]["class"] == 1
                ]
            )
        )
        ikr += 1

# Terapkan Laplace smoothing
for k in range(len(data.columns) - 1):
    for l in range(len(model[k])):
        model[k][l] = [n + 1 for n in model[k][l]]

# Ubah frekuensi menjadi probabilitas
for m in range(len(data.columns) - 1):
    for n in range(len(model[m])):
        model[m][n] = [x / sum(model[m][n]) for x in model[m][n]]


# Hitung probabilitas kelas menggunakan Naive Bayes
def hitung(a, b, c, d, e, f):
    for n in range(len(data["class"].unique())):
        nilai_prob[n] = (
            model[0][a][n]
            * model[1][b][n]
            * model[2][c][n]
            * model[3][d][n]
            * model[4][e][n]
            * model[5][f][n]
            * (len(data[data["class"] == n]) / len(data))
        )

        total = sum(nilai_prob.values())

    for i in range(len(nilai_prob)):
        nilai_prob[i] = nilai_prob[i] / total


# Cetak prediksi atau kembalikan label kelas


def penentu(test=False):
    if nilai_prob[0] > nilai_prob[1] and test == False:
        print(nama, "| Result : No")
        print(nilai_prob)
    elif nilai_prob[0] > nilai_prob[1] and test == True:
        return 0
    elif nilai_prob[0] < nilai_prob[1] and test == False:
        print(nama, "| Result : Yes")
        print(nilai_prob)
    else:
        return 1


# Simpan probabilitas hasil prediksi
nilai_prob = {}


def inputNumber(prompt):
    while True:
        try:
            num = float(input(prompt))
            break
        except ValueError:
            pass
    return num


def displayMenu(options):
    for i in range(len(options)):
        print("{:d}. {:s}".format(i + 1, options[i]))

    choice = 0
    while not (any(choice == arange(len(options)) + 1)):
        choice = inputNumber("Masukkan Pilihan: ")

    return choice


# Daftar pilihan menu
menuItems = array(
    [
        "Masukkan Data",
        "Tampilkan Prediksi",
        "Tampilkan Nilai Tiap Kolom",
        "Evaluasi Model",
        "Keluar",
    ]
)

# Baca data uji
data_uji = pd.read_csv("monk_uji.csv")

# Simpan hasil prediksi data uji
hasil = []

for i in range(len(data_uji)):
    nilai_prob = {}
    hitung(
        data_uji.loc[i][1] - 1,
        data_uji.loc[i][2] - 1,
        data_uji.loc[i][3] - 1,
        data_uji.loc[i][4] - 1,
        data_uji.loc[i][5] - 1,
        data_uji.loc[i][6] - 1,
    )
    hasil.append(penentu(test=True))

# Inisialisasi nilai evaluasi
betul, tp, tn, fp, fn = 0, 0, 0, 0, 0

# Hitung akurasi dan elemen confusion matrix
for i in range(len(hasil)):
    if hasil[i] == data_uji["class"][i]:
        betul += 1

    if hasil[i] == 0 and data_uji["class"][i] == 0:  # True negative
        tn += 1

    if hasil[i] == 0 and data_uji["class"][i] == 1:  # False negative
        fn += 1

    if hasil[i] == 1 and data_uji["class"][i] == 0:  # False positive
        fp += 1

    if hasil[i] == 1 and data_uji["class"][i] == 1:  # True positive
        tp += 1

while True:
    # Tampilkan menu utama
    choice = displayMenu(menuItems)

    # Minta atribut untuk data yang akan diprediksi
    if choice == 1:
        sp.call("cls", shell=True)
        global nama, head_shape, body_shape, is_smiling, holding, jacket_color, has_tie
        nama = input("Name :")
        _head_shape = input("Head Shape (1-3) :")
        _body_shape = input("Body Shape (1-3) :")
        _is_smiling = input("Is Smiling (1-2) :")
        _holding = input("Is Holding (1-3) :")
        _jacket_color = input("Jacket Color (1-4) :")
        _has_tie = input("Has Tie (1-2) :")
        # Ubah nilai atribut menjadi indeks kategori
        head_shape = int(_head_shape)
        body_shape = int(_body_shape)
        is_smiling = int(_is_smiling)
        holding = int(_holding)
        jacket_color = int(_jacket_color)
        has_tie = int(_has_tie)

    # Tampilkan prediksi
    elif choice == 2:
        sp.call("cls", shell=True)
        hitung(
            head_shape - 1,
            body_shape - 1,
            is_smiling - 1,
            holding - 1,
            jacket_color - 1,
            has_tie - 1,
        )
        penentu()

    # Tampilkan data dan probabilitas prediksi
    elif choice == 3:
        sp.call("cls", shell=True)
        print(nama, head_shape, body_shape, is_smiling, holding, jacket_color, has_tie)
        print(nilai_prob)

    # Tampilkan metrik evaluasi
    elif choice == 4:
        sp.call("cls", shell=True)

        print(
            "-Confusion Matrix- \nTrue Negative:",
            tn,
            "\nFalse Negative :",
            fn,
            "\nFlase Positive :",
            fp,
            "\nTrue Positive",
            tp,
        )

        print("\n\nAkurasi :", betul / len(hasil) * 100, "%\n")
        print("Recall :", tp / (tp + fn))
        print("Precison :", tp / (tp + fp))

    # Keluar dari program
    elif choice == 5:
        break
