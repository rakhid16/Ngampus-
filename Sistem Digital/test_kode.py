"""Regresi kalkulator BCD; membutuhkan Python 3 dan compiler C11."""

import os
from pathlib import Path
import random
import shlex
import subprocess
import tempfile
import unittest


SOURCE = Path(__file__).resolve().with_name("KODE.c")
MIN = -(1 << 63)
MAX = (1 << 63) - 1
SEGMENTS = ("abcdef", "bc", "abdeg", "abcdg", "bcfg", "acdfg",
            "acdefg", "abc", "abcdefg", "abcdfg")


class CalculatorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix="bcd-tests-")
        cls.addClassCleanup(cls.temp.cleanup)
        directory = Path(cls.temp.name)
        cls.program = directory / "calculator"
        cls.harness = directory / "arithmetic"
        compiler = shlex.split(os.environ.get("CC", "cc"))
        flags = shlex.split(os.environ.get("CFLAGS", ""))
        flags += ["-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Werror"]
        subprocess.run(compiler + flags + [str(SOURCE), "-o", str(cls.program)],
                       check=True, capture_output=True, text=True, timeout=60)
        harness_source = directory / "arithmetic.c"
        harness_source.write_text('''#define main calculator_main
#include "KODE.c"
#undef main
int main(void) {
  int operation;
  long long left, right, result;
  while (scanf("%d %lld %lld", &operation, &left, &right) == 3) {
    if (calculate(operation, left, right, &result))
      printf("%lld\\n", result);
    else
      puts("invalid");
  }
  return 0;
}
''')
        subprocess.run(compiler + flags + ["-I", str(SOURCE.parent),
                       str(harness_source), "-o", str(cls.harness)],
                       check=True, capture_output=True, text=True, timeout=60)

    def run_program(self, data):
        return subprocess.run([str(self.program)], input=data, text=True,
                              capture_output=True, timeout=10)

    def test_arithmetic_boundaries_and_random_values(self):
        values = [MIN, MIN + 1, -3037000500, -2, -1, 0, 1, 2,
                  3037000500, MAX - 1, MAX]
        cases = [(op, a, b) for op in range(1, 5)
                 for a in values for b in values]
        rng = random.Random(2026)
        cases += [(rng.randrange(1, 5), rng.randint(MIN, MAX),
                   rng.randint(MIN, MAX)) for _ in range(2000)]
        cases += [(0, 1, 2), (5, 1, 2)]
        expected = []
        for op, left, right in cases:
            if op == 1:
                value = left + right
            elif op == 2:
                value = left - right
            elif op == 3:
                value = left * right
            elif op == 4 and right:
                value = abs(left) // abs(right)
                if (left < 0) != (right < 0):
                    value = -value
            else:
                expected.append("invalid")
                continue
            expected.append(str(value) if MIN <= value <= MAX else "invalid")
        data = "".join(f"{op} {a} {b}\n" for op, a, b in cases)
        result = subprocess.run([str(self.harness)], input=data, text=True,
                                capture_output=True, timeout=10)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.splitlines(), expected)
        self.assertEqual(result.stderr, "")

    def test_segment_encoding(self):
        for value in (0, 1234567890, -9876543210, MIN, MAX):
            with self.subTest(value=value):
                result = self.run_program(f"1\n{value}\n0\n5\n")
                self.assertEqual(result.returncode, 0, result.stderr)
                encoded = ("g " if value < 0 else "")
                encoded += "".join(SEGMENTS[int(d)] + " "
                                   for d in str(abs(value)))
                self.assertIn(f"Hasil operasi: {value}\n", result.stdout)
                self.assertIn(f"Hasil dalam kode segmen: {encoded}\n", result.stdout)

    def test_invalid_operation_recovers(self):
        result = self.run_program(f"9\n1\n{MAX}\n1\n4\n1\n0\n1\n2\n3\n5\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Operasi tidak ditemukan.", result.stdout)
        self.assertEqual(result.stdout.count("Operasi tidak valid:"), 2)
        self.assertIn("Hasil operasi: 5\n", result.stdout)

    def test_invalid_numbers_are_rejected(self):
        for value in ("abc", "1x", "", str(MAX + 1), str(MIN - 1), "9" * 200):
            with self.subTest(value=value):
                result = self.run_program(f"1\n{value}\n0\n5\n")
                self.assertEqual(result.returncode, 1)
                self.assertIn("Masukan harus", result.stderr)
                self.assertNotIn("Hasil operasi:", result.stdout)

    def test_eof_and_invalid_menu(self):
        self.assertEqual(self.run_program("").returncode, 0)
        for data in ("x", "1x\n", str(MAX + 1), "1\n", "1\n2\n"):
            with self.subTest(data=data):
                result = self.run_program(data)
                self.assertEqual(result.returncode, 1)
                self.assertNotIn("Hasil operasi:", result.stdout)
        result = self.run_program("1\n2\n3")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("Hasil operasi: 5\n", result.stdout)


if __name__ == "__main__":
    unittest.main(verbosity=2)
