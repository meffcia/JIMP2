#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readTree.h"
#include "decompress.h"

int main(int argc, char *argv[]) {
  char *in_file = NULL;
  char *out_file = NULL;
  struct ASCII_Code codes[256];

  // ustawienie nazw plików wejściowych i wyjściowych na podstawie argumentów programu
  if (argc >= 2) {
    in_file = argv[1];
  } else {
    printf("Nie podano pliku wejściowego!\n");
    return -1;
  }

  if (argc >= 3) {
    out_file = argv[2];
  } else {
    printf("Nie podano pliku wyjściowego!\n");
    return -1;
  }

  FILE *in = fopen(in_file, "rb");
  if (in == NULL) {
    printf("Nie można otworzyć pliku wejściowego: %s\n", in_file);
    return -1;
  }

  FILE *out = fopen(out_file, "w");
  if (out == NULL) {
    printf("Nie można otworzyć pliku wyjściowego: %s\n", out_file);
    fclose(in);
    return -1;
  }

  // odczytanie kodów ASCII z pliku wejściowego i dekompresja danych
  int num_codes = read_file(codes);
  if (num_codes == -1) {
    printf("Błąd odczytu kodów ASCII z pliku wejściowego!\n");
    fclose(in);
    fclose(out);
    return -1;
  }

  decode(in, out, codes);

  fclose(in);
  fclose(out);

  return 0;
}

