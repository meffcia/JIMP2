#ifndef BIT_H
#define BIT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Bitstream {
    unsigned char buffer;  // bufor, w którym trzymany jest bieżący bajt
    int numBits;           // liczba bitów, które zostały zapisane w buforze
    FILE *file;            // plik, do którego zapisywane są bity
} Bitstream;

Bitstream *createBitstream(FILE *file);

void writeBit(unsigned int bit, Bitstream *bitstream);

void flushBitstream(Bitstream *bitstream);

void closeBitstream(Bitstream *bitstream);

#endif // BIT_H