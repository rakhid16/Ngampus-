"""CLI regressions: python3 'Struktur Data/test_programs.py'.

Requires a C compiler (CC, default: cc). CC and optional CFLAGS are parsed
with shlex; strict C11 flags are always appended. No third-party packages.
All binaries and the generated Checker harness live in a temporary directory.
"""

import os
from pathlib import Path
import re
import shlex
import subprocess
import tempfile
import unittest


SOURCE_DIR = Path(__file__).resolve().parent
PROGRAMS = {
    "single": "Single Linked List.c",
    "circular": "Circular Linked List.c",
    "doubly": "Doubly Linked List.c",
    "stack": "Stack.c",
    "queue": "Queue.c",
    "checker": "Checker - Stack.c",
    "final": "Final Project.c",
}
STRICT_FLAGS = ["-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Werror"]

CHECKER_HARNESS = r'''
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define main checker_program_main
#include "Checker - Stack.c"
#undef main

int main(int argc, char **argv) {
  if (argc != 2)
    return 2;
  if (strcmp(argv[1], "balanced") == 0) {
    const char *cases[] = {"", "plain text", "()[]{}", "{a[2] + (b)}",
                           "([{}])([])"};
    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
      if (isBalanced(cases[i]) != 1) {
        fprintf(stderr, "Rejected balanced expression: %s\n", cases[i]);
        return 1;
      }
    }
  } else if (strcmp(argv[1], "mismatched") == 0) {
    const char *cases[] = {"(", ")", "([)]", "{[}]", "())", "[[]"};
    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
      if (isBalanced(cases[i]) != 0) {
        fprintf(stderr, "Accepted mismatched expression: %s\n", cases[i]);
        return 1;
      }
    }
  } else if (strcmp(argv[1], "deep") == 0) {
    const size_t depth = 10000;
    char *text = malloc(2 * depth + 1);
    if (text == NULL)
      return 2;
    for (size_t i = 0; i < depth; i++) {
      text[i] = "([{"[i % 3];
      text[2 * depth - 1 - i] = ")]}"[i % 3];
    }
    text[2 * depth] = '\0';
    int balanced = isBalanced(text);
    text[2 * depth - 1] = ']';
    int mismatched = isBalanced(text);
    free(text);
    if (balanced != 1 || mismatched != 0) {
      fputs("Incorrect result for deeply nested brackets\n", stderr);
      return 1;
    }
  } else {
    return 2;
  }
  puts("OK");
  return 0;
}
'''


def run_checked(command, cwd, input_text="", timeout=10):
    """Fail with the command and captured output rather than hiding CLI errors."""
    label = " ".join(shlex.quote(str(part)) for part in command)
    try:
        result = subprocess.run(
            command,
            cwd=cwd,
            input=input_text,
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
            timeout=timeout,
            check=False,
        )
    except (OSError, subprocess.TimeoutExpired) as error:
        raise AssertionError("Could not finish {}: {}".format(label, error)) from error
    if result.returncode != 0:
        raise AssertionError(
            "{} exited with {}\nstdout:\n{}\nstderr:\n{}".format(
                label, result.returncode, result.stdout, result.stderr
            )
        )
    return result


class ProgramTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix="ngampus-regression-")
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.build_dir = Path(cls.temporary.name)
        compiler = shlex.split(os.environ.get("CC", "cc"))
        if not compiler:
            raise ValueError("CC must name a C compiler")
        flags = shlex.split(os.environ.get("CFLAGS", "")) + STRICT_FLAGS
        cls.binaries = {}
        suffix = ".exe" if os.name == "nt" else ""
        for name, filename in PROGRAMS.items():
            binary = cls.build_dir / (name + suffix)
            run_checked(
                compiler + flags + [str(SOURCE_DIR / filename), "-o", str(binary)],
                cls.build_dir,
                timeout=60,
            )
            cls.binaries[name] = binary

        harness = cls.build_dir / "checker_harness.c"
        harness.write_text(CHECKER_HARNESS, encoding="utf-8")
        cls.checker_harness = cls.build_dir / ("checker_harness" + suffix)
        run_checked(
            compiler + flags + [
                "-I", str(SOURCE_DIR), str(harness), "-o", str(cls.checker_harness)
            ],
            cls.build_dir,
            timeout=60,
        )

    def run_program(self, name, *lines):
        text = "\n".join(str(line) for line in lines) + ("\n" if lines else "")
        result = run_checked([str(self.binaries[name])], self.build_dir, text)
        self.assertEqual(result.stderr, "")
        return result.stdout

    def test_empty_and_blank_eof(self):
        for name in PROGRAMS:
            for lines in [(), ("",)]:
                with self.subTest(program=name, lines=lines):
                    self.assertTrue(self.run_program(name, *lines))

    def test_eof_during_input(self):
        partial_inputs = {
            "single": [1, 101, "Satu", "l", "Alamat", 1, 202, "Dua"],
            "circular": [1, "Satu", "l", 170, 1, "Dua"],
            "doubly": [1, 101, "Satu", "TI", 1, 3, 101, "Baru"],
            "stack": [1, 10, 1],
            "queue": [1, 1, "AB123", "SUV", "Honda", 1, 2],
            "checker": [2],
            "final": [1, 1, 1, 1, 4, 2, "admin"],
        }
        for name, lines in partial_inputs.items():
            with self.subTest(program=name):
                self.run_program(name, *lines)

    def test_invalid_numeric_input_then_exit(self):
        exits = dict(single="q", circular=4, doubly="q", stack=7,
                     queue=8, checker=3, final=3)
        for name, exit_choice in exits.items():
            with self.subTest(program=name):
                output = self.run_program(name, "invalid", "9" * 200, exit_choice)
                self.assertIn("valid", output.lower())

    def test_empty_operations(self):
        cases = {
            "single": ([4, 3, 999, "q"], ["NULL", "Tidak ada data seperti itu"]),
            "circular": ([2, 3, 4], ["data kosong"]),
            "doubly": ([2, 4, 5, 2, "q"], ["Tidak ada data yang akan dihapus"]),
            "stack": ([2, 4, 3, 5, 8, 9, 7],
                      ["Stack is empty", "NULL", "jumlah stack : 0", "jumlah isi stack : 0"]),
            "queue": ([2, 3, 4, 5, 6, 7, 8],
                      ["Queue is Empty", "Antrian kosong", "Belum untung"]),
            "final": ([2, "admin", "admin", 1, 2, 4, 5, 3],
                      ["Kosong", "Tidak ada antrian", "Belum ada pemesanan"]),
        }
        for name, (lines, messages) in cases.items():
            with self.subTest(program=name):
                output = self.run_program(name, *lines)
                for message in messages:
                    self.assertIn(message, output)

    def test_stack_lifo_search_count_and_sum(self):
        output = self.run_program(
            "stack", 1, 10, 1, 20, 2, 3, 5, 8, 6, 10, 6, 99, 4, 2, 7
        )
        self.assertEqual(re.findall(r"\|\s*(-?\d+)\s*\|", output), ["20", "10"])
        self.assertIn("Top Element of Stack : 20", output)
        self.assertIn("Top Element of Stack : 10", output)
        self.assertIn("jumlah stack : 2", output)
        self.assertIn("jumlah isi stack : 30", output)
        self.assertIn("Key Found", output)
        self.assertIn("Key Not Found", output)

    def test_queue_fifo_reverse_revenue_and_reuse(self):
        output = self.run_program(
            "queue", 1, 1, "AB1", "SUV", "Honda",
            1, 2, "AB2", "Sedan", "Toyota", 3, 4, 5, 6, 2, 2, 7,
            1, 3, "AB3", "Van", "Suzuki", 3, 8,
        )
        self.assertEqual(re.findall(r"Nomor antrian\s+(\d+)", output), ["1", "2", "3"])
        self.assertEqual(re.findall(r"Nomor antrian : (\d+)", output), ["2", "1"])
        self.assertEqual(re.findall(r"selesai dicuci: (\d+)", output), ["1", "2"])
        self.assertIn("antrian mobil paling depan", output)
        self.assertIn("antrian mobil paling belakang", output)
        self.assertIn("Untung hari in boz! : 60000", output)
        self.assertIn("Nomor plat        AB3", output)

    def test_single_update_preserves_second_record(self):
        # Insertion is at the head: updating 202 must retain the node for 101.
        output = self.run_program(
            "single", 1, 101, "Satu", "l", "Alamat satu",
            1, 202, "Dua", "p", "Alamat dua",
            2, 202, "Dua baru", "p", "Alamat baru", 4, "q",
        )
        self.assertEqual(re.findall(r"NRP'nya\s*:\s*(\d+)", output), ["202", "101"])
        self.assertEqual(re.findall(r"NAMA'nya\s*:\s*([^\n]+)", output),
                         ["Dua baru", "Satu"])
        self.assertIn("Alamat baru", output)

    def test_doubly_filter_non_head(self):
        output = self.run_program(
            "doubly", 1, 101, "Satu", "TI", 2,
            1, 202, "Dua", "SI", 1, 1, 303, "Tiga", "TI", 2, 5, 1, "q",
        )
        self.assertEqual(re.findall(r"NPM'nya\s*:\s*(\d+)", output), ["202"])
        self.assertEqual(re.findall(r"NAMA'nya\s*:\s*([^\n]+)", output), ["Dua"])

    def test_circular_delete_sole_then_add(self):
        for deletion in [(2, 1), (2, 2, 170)]:
            with self.subTest(deletion=deletion):
                output = self.run_program(
                    "circular", 1, "Sole", "l", 170, *deletion,
                    3, 1, "Baru", "p", 180, 3, 4,
                )
                self.assertIn("data kosong", output)
                last_listing = output.rsplit("Data Mahasiswa yang Kemping\n\n", 1)[-1]
                self.assertEqual(re.findall(r"Nama\s*:\s*([^\n]+)", last_listing), ["Baru"])

    def test_circular_delete_tail_then_add(self):
        output = self.run_program(
            "circular", 1, "Tail", "l", 170, 1, "Head", "p", 180,
            2, 2, 999, 2, 2, 170, 1, "Baru", "l", 190, 3, 4,
        )
        self.assertIn("Data tidak ditemukan", output)
        last_listing = output.rsplit("Data Mahasiswa yang Kemping\n\n", 1)[-1]
        self.assertEqual(re.findall(r"Nama\s*:\s*([^\n]+)", last_listing), ["Baru", "Head"])

    def test_checker_cli(self):
        output = self.run_program("checker", 1, 2, 2, 3)
        self.assertIn("function showUsername", output)
        self.assertEqual(output.count("HASIL COMPILE : VALID!"), 2)
        self.assertNotIn("TIDAK VALID!", output)

    def test_checker_balanced_mismatched_and_deep(self):
        for case in ["balanced", "mismatched", "deep"]:
            with self.subTest(case=case):
                result = run_checked(
                    [str(self.checker_harness), case], self.build_dir
                )
                self.assertEqual(result.stdout, "OK\n")
                self.assertEqual(result.stderr, "")

    def test_final_duplicate_pending_and_confirmed(self):
        output = self.run_program(
            "final", 1, 1, 1, 7, 1, 1, 7, 1, 2, 7, 4,
            2, "admin", "admin", 2, 2, 4, 5,
            1, 1, 1, 7, 1, 2, 7, 4, 3,
        )
        self.assertEqual(output.count("Sudah terpesan/masuk daftar antrian"), 3)
        self.assertEqual(output.count("terpesan!"), 2)
        self.assertRegex(output, r"Laba total\s*:\s*Rp 45000\b")

    def test_final_full_seats_and_totals(self):
        lines = [1]
        films = ["FORREST GUMP", "PAPER TOWN", "VENOM"]
        expected = []
        for film_number, film in enumerate(films, 1):
            for seat in range(1, 31):
                lines.extend([1, film_number, seat])
                expected.append((str(seat), film))
        lines.extend([4, 2, "admin", "admin"] + [2] * 91 + [3, 4, 5, 3])
        output = self.run_program("final", *lines)
        bookings = re.findall(
            r"Kursi nomor (\d+) dari film (FORREST GUMP|PAPER TOWN|VENOM) terpesan!",
            output,
        )
        self.assertEqual(bookings, expected)
        self.assertIn("Tidak ada antrian", output)
        self.assertEqual(output.count("SEMUA KURSI SUDAH DIPESAN!"), 3)
        for film, total in zip(films, [600000, 750000, 900000]):
            self.assertRegex(output, r"Laba dari film " + film + r" adalah\s*:\s*Rp " + str(total) + r"\b")
        self.assertRegex(output, r"Laba total\s*:\s*Rp 2250000\b")


if __name__ == "__main__":
    unittest.main(verbosity=2)
