#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(int argc, char *argv[]) {
    int i;
    int c;
    int frequencies[256] = {0};
    int result = 0;
    char str[256];

    FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;

    if (in != NULL) {
        while ((c = fgetc(in)) != EOF) {
            frequencies[c]++;
        }
        

        HuffNode *root = createHuffmanTree(frequencies);

        FILE *out = fopen("tree.txt", "w");
        writeTree(root, str, out);
        fclose(out);

        freeTree(root);


    	// zamknięcie plików
    	fclose(in);

    } 
    else {
        printf("Nie podano nazwy pliku \n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}



