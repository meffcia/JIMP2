#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readTree.h"

int read_file(struct ASCII_Code codes[]) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    FILE* file;
    file = fopen("tree.txt", "r");
    if (file == NULL) {
        printf("Błąd pliku.");
        return -1;
    }
    while ((read = getline(&line, &len, file)) != -1) {
    char* token;
    token = strtok(line, " ");
    codes[i].ascii = atoi(token);
    token = strtok(NULL, " ");
    token[strcspn(token, "\n")] = 0; // usuń znak nowej linii
    strcpy(codes[i].binary, token);
    i++;
    }

    fclose(file);
    free(line);
    return 0;
}
