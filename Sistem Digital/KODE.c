#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *const digit_segments[] = {
    "abcdef", "bc", "abdeg", "abcdg", "bcfg",
    "acdfg",  "acdefg", "abc",  "abcdefg", "abcdfg",
};

static int read_integer(const char *prompt, long long *value) {
  char input[128], *end;
  long long parsed;

  printf("%s", prompt);
  fflush(stdout);
  if (fgets(input, sizeof(input), stdin) == NULL)
    return feof(stdin) && !ferror(stdin) ? -1 : 0;

  if (strchr(input, '\n') == NULL && !feof(stdin)) {
    int ch = getchar();
    if (ch != '\n' && ch != EOF) {
      while ((ch = getchar()) != '\n' && ch != EOF) {
      }
      return 0;
    }
  }

  errno = 0;
  parsed = strtoll(input, &end, 10);
  if (end == input || errno == ERANGE)
    return 0;
  while (isspace((unsigned char)*end))
    end++;
  if (*end != '\0' || ferror(stdin))
    return 0;

  *value = parsed;
  return 1;
}

static int calculate(int operation, long long left, long long right,
                     long long *result) {
  switch (operation) {
  case 1:
    if ((right > 0 && left > LLONG_MAX - right) ||
        (right < 0 && left < LLONG_MIN - right))
      return 0;
    *result = left + right;
    return 1;
  case 2:
    if ((right > 0 && left < LLONG_MIN + right) ||
        (right < 0 && left > LLONG_MAX + right))
      return 0;
    *result = left - right;
    return 1;
  case 3:
    if (left > 0) {
      if ((right > 0 && left > LLONG_MAX / right) ||
          (right < 0 && right < LLONG_MIN / left))
        return 0;
    } else if (left < 0) {
      if ((right > 0 && left < LLONG_MIN / right) ||
          (right < 0 && left < LLONG_MAX / right))
        return 0;
    }
    *result = left * right;
    return 1;
  case 4:
    if (right == 0 || (left == LLONG_MIN && right == -1))
      return 0;
    *result = left / right;
    return 1;
  default:
    return 0;
  }
}

static void print_digit(unsigned int digit) {
  printf("%s ", digit_segments[digit]);
}

static void print_number(long long value) {
  unsigned long long magnitude;
  unsigned int digits[sizeof(value) * CHAR_BIT];
  size_t count = 0;

  if (value < 0) {
    printf("g ");
    magnitude = (unsigned long long)(-(value + 1)) + 1;
  } else {
    magnitude = (unsigned long long)value;
  }

  do {
    digits[count++] = (unsigned int)(magnitude % 10);
    magnitude /= 10;
  } while (magnitude != 0);

  while (count > 0)
    print_digit(digits[--count]);
}

int main(void) {
  long long choice, left, right, result;
  int operation, input_status;

  for (;;) {
    printf("\nPROGRAM KALKULATOR BCD DECODER\n");
    printf("1. Penjumlahan\n2. Pengurangan\n3. Perkalian\n");
    printf("4. Pembagian\n5. Keluar\n");

    input_status = read_integer("Pilihan: ", &choice);
    if (input_status <= 0) {
      if (input_status == -1)
        return 0;
      fputs("Pilihan harus berupa bilangan bulat dalam rentang long long.\n", stderr);
      return 1;
    }

    if (choice == 5) {
      puts("Terima kasih telah menggunakan program ini.");
      return 0;
    }

    if (choice < 1 || choice > 4) {
      puts("Operasi tidak ditemukan.");
      continue;
    }
    operation = (int)choice;

    if (read_integer("Angka pertama: ", &left) <= 0 ||
        read_integer("Angka kedua: ", &right) <= 0) {
      fputs("Masukan harus berupa bilangan bulat.\n", stderr);
      return 1;
    }

    if (!calculate(operation, left, right, &result)) {
      puts("Operasi tidak valid: pembagian dengan nol atau hasil di luar rentang long long.");
      continue;
    }

    printf("Hasil operasi: %lld\n", result);
    printf("Angka pertama dalam kode segmen: ");
    print_number(left);
    printf("\nAngka kedua dalam kode segmen: ");
    print_number(right);
    printf("\nHasil dalam kode segmen: ");
    print_number(result);
    putchar('\n');
  }
}
