#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "koduj.h"
#include "bit.h"

int main(int argc, char *argv[]) {
    int i;
    int c;
    int frequencies[256] = {0};
    unsigned int codes[256] = {0};
    int result = 0;

    FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;

    if (in != NULL) {
        while ((c = fgetc(in)) != EOF) {
            frequencies[c]++;
        }
        

        HuffNode *root = createHuffmanTree(frequencies, codes);

        FILE *out = fopen("tree.txt", "w");
        writeTreeToFile(root, out);
        fclose(out);

        printCodes(root, codes);

        freeTree(root);

FILE *wynik = fopen("output.txt", "w");
    if (wynik == NULL) {
        printf("Błąd: nie udało się otworzyć pliku wyjściowego\n");
        fclose(in);
        return 1;
    }

    // wywołanie funkcji compressFile
    compressFile(in, wynik, codes);

    // zamknięcie plików
    fclose(in);
    fclose(wynik);

    } else {
        printf("Nie podano nazwy pliku \n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}



