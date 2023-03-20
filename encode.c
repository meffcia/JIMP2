#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ASCII_Code {
    int ascii;
    char binary[1000]; 
};


int read_file(struct ASCII_Code codes[]) {
    char line[256];
    int i = 0;
    FILE *file;
    file = fopen("tree.txt", "r");
    if (file == NULL)
    {
        printf("Błąd pliku.");
        return -1;
    }
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        codes[i].ascii = atoi(token);
        token = strtok(NULL, " ");
        strcpy(codes[i].binary, token);
        i++;
    }
    fclose(file);
    return 0;
}

void encode_file(struct ASCII_Code codes[], char *file_name) {
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Błąd pliku.");
        return;
    }
    char c;
    while ((c = fgetc(file)) != EOF) {
        for (int i = 0; i < 256; i++) {
            if (codes[i].ascii == (int)c) {
                printf("%s", codes[i].binary);
            }
        }
    }

    fclose(file);
}

int main() {
    struct ASCII_Code codes[256];
    read_file(codes);
    encode_file(codes, "test.txt");
    return 0;
}
