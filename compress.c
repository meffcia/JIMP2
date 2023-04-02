#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readTree.h"
#include "compress.h"

void encode_file(struct ASCII_Code codes[], FILE *in, FILE *out) {
    char c;
    unsigned char bit_buffer = 0;
    int num_bits_in_buffer = 0;
    int num_bits_to_pad = 0; // liczba bitów do dopisania na końcu
    int num_bits_last_byte = 0; // liczba dopisanych zer do ostatniego bajtu
    unsigned char first_byte = 0; // pusty bajt na początku pliku
    fwrite(&first_byte, 1, 1, out); // zapis pustego bajtu do pliku
    while ((c = fgetc(in)) != EOF) {
        for (int i = 0; i < 256; i++) {
            if (codes[i].ascii == (int)c) {
                int num_bits_to_write = strlen(codes[i].binary);
                char *binary_code = codes[i].binary;
                for (int j = 0; j < num_bits_to_write; j++) {
                    bit_buffer <<= 1;
                    if (binary_code[j] == '1') {
                        bit_buffer |= 1;
                    } 
                    num_bits_in_buffer++;
                    if (num_bits_in_buffer == 8) {
                        fwrite(&bit_buffer, 1, 1, out); // zapis do pliku binarnego
                        bit_buffer = 0;
                        num_bits_in_buffer = 0;
                    }
                }
            }
        }
    }
    // Obliczanie liczby bitów do dopisania na końcu
    if (num_bits_in_buffer > 0) {
        num_bits_to_pad = 8 - num_bits_in_buffer;
        num_bits_last_byte = num_bits_to_pad;
        bit_buffer <<= num_bits_to_pad;
        fwrite(&bit_buffer, 1, 1, out); // zapis do pliku binarnego
    }
    
    // Zapisywanie liczby dopisanych zer do ostatniego bajtu jako pierwszy bajt w pliku
    unsigned char last_byte = num_bits_last_byte;
    fseek(out, 0, SEEK_SET);
    fwrite(&last_byte, 1, 1, out); // zapis liczby do pierwszego bajtu
    printf("Liczba dopisanych zer: %d\n", num_bits_last_byte);
}






