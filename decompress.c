#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readTree.h"
#include "decompress.h"

void decode(FILE *in, FILE *out, struct ASCII_Code codes[]) {
  unsigned char buffer[4];
  int bytes_read;
  char bits[32];
  bits[0] = '\0';
  int bits_len = 0;
  int num_zeros = 0;

  

  // Read first byte to get number of trailing zeros in last byte
  if ((bytes_read = fread(buffer, 1, 1, in)) != 1) {
    printf("Nie udało się odczytać liczby zer.");
    return;
  }
  num_zeros = buffer[0];

  // Read rest of the file
  while ((bytes_read = fread(buffer, 1, 4, in)) == 4) {
    for (int i = 0; i < 4; i++) {
      for (int j = 7; j >= 0; j--) {
        int bit = (buffer[i] >> j) & 1;
        bits[bits_len++] = bit + '0';
        bits[bits_len] = '\0';

        for (int k = 0; k < 256; k++) {
          if (strcmp(bits, codes[k].binary) == 0) {
            fprintf(out, "%c", codes[k].ascii);
            bits[0] = '\0';
            bits_len = 0;
            break;
          }
        }
      }
    }
  }

  // Process last incomplete byte
if (bytes_read > 0) {
  for (int i = 0; i < bytes_read; i++) {
    int bits_to_read = (i == bytes_read - 1) ? 8 - num_zeros : 8;
    for (int j = 7; j >= 8 - bits_to_read; j--) {
      int bit = (buffer[i] >> j) & 1;
      bits[bits_len++] = bit + '0';
      bits[bits_len] = '\0';

      for (int k = 0; k < 256; k++) {
        if (strcmp(bits, codes[k].binary) == 0) {
          fprintf(out, "%c", codes[k].ascii);
          bits[0] = '\0';
          bits_len = 0;
          break;
          }
        }
      }
    }
  }
}



