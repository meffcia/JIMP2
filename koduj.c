#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "bit.h"

void compressFile(FILE *inputFile, FILE *outputFile, unsigned int *codes) {
    
    // inicjalizacja bitstreamu
    Bitstream *bitstream = createBitstream(outputFile);

    // zapisanie tablicy kodów w nagłówku pliku wyjściowego
    for (int i = 0; i < 256; i++) {
        if (codes[i] > 0) {
            fprintf(outputFile, "%c %u ", i, codes[i]);
        }
    }
    fprintf(outputFile, "\n");

    // odczytanie pliku wejściowego po jednym bajcie i zapisanie kodów znakowych
    unsigned char byte;
    while (fread(&byte, sizeof(unsigned char), 1, inputFile) == 1) {
        unsigned int code = codes[byte];
        char codeStr[33];
        for (int i = 31; i >= 0; i--) {
            unsigned int bit = (code >> i) & 1;
            codeStr[31 - i] = (bit ? '1' : '0');
        }
        codeStr[32] = '\0';
        fprintf(outputFile, "%s", codeStr);
    }

    // zakończenie zapisywania bitstreamu
    flushBitstream(bitstream);

}

