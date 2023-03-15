#include <stdio.h>
#include <stdlib.h>
#include "bit.h"


Bitstream *createBitstream(FILE *file) {
    Bitstream *bitstream = (Bitstream *)malloc(sizeof(Bitstream));
    if (bitstream == NULL) {
        fprintf(stderr, "Error: could not allocate memory for bitstream\n");
        exit(1);
    }
    bitstream->buffer = 0;
    bitstream->numBits = 0;
    bitstream->file = file;
    return bitstream;
}

void writeBit(unsigned int bit, Bitstream *bitstream) {
    if (bit != 0 && bit != 1) {
        fprintf(stderr, "Error: invalid bit value\n");
        exit(1);
    }
    bitstream->buffer = (bitstream->buffer << 1) | bit;
    bitstream->numBits++;
    if (bitstream->numBits == 8) {
        flushBitstream(bitstream);
    }
}

void flushBitstream(Bitstream *bitstream) {
    if (bitstream->numBits == 0) {
        return;
    }
    fwrite(&bitstream->buffer, sizeof(unsigned char), 1, bitstream->file);
    bitstream->buffer = 0;
    bitstream->numBits = 0;
}

void closeBitstream(Bitstream *bitstream) {
    flushBitstream(bitstream);
    free(bitstream);
}

