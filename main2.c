#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "makeTree.h"
#include "readTree.h"
#include "compress.h"

int main(int argc, char * argv[]) {
    int i;
    int c;
    int frequencies[256] = {0};
    int result = 0;
    char * in_file = NULL;
    char * out_file = NULL;
    char * path = NULL;
    char str[256];
    int compress = 0;
    int decompress = 0;
    struct ASCII_Code codes[256];

    // Sprawdzenie liczby argumentów programu
    if (argc < 3) {
        printf("Użycie: %s plik_wejsciowy plik_wyjsciowy\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Pobranie nazw plików z argumentów
    in_file = argv[1];
    out_file = argv[2];

    // Otwarcie pliku wejściowego i zliczanie częstości występowania znaków
    FILE *in = fopen(in_file, "r");
    if (in == NULL) {
        printf("Nie udało się otworzyć pliku wejściowego.\n");
        return EXIT_FAILURE;
    }

    while ((c = fgetc(in)) != EOF) {
        frequencies[c]++;
    }

    fclose(in);

    // Tworzenie drzewa Huffmana i zapisywanie go do pliku
    HuffNode *root = createHuffmanTree(frequencies);

    FILE *tree = fopen("tree.txt", "w");
    if (tree == NULL) {
        printf("Nie udało się utworzyć pliku drzewa.\n");
        return EXIT_FAILURE;
    }

    writeTree(root, str, tree);
    fclose(tree);
    freeTree(root);

    // Kompresja pliku
    FILE *in2 = fopen(in_file, "r");
    if (in2 == NULL) {
        printf("Nie udało się otworzyć pliku wejściowego.\n");
        return EXIT_FAILURE;
    }

    FILE *out = fopen(out_file, "wb");
    if (out == NULL) {
        printf("Nie udało się utworzyć pliku wyjściowego.\n");
        fclose(in2);
        return EXIT_FAILURE;
    }

    read_file(codes);
    encode_file(codes, in2, out);
    fclose(in2);
    fclose(out);

    return EXIT_SUCCESS;
}
