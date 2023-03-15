#ifndef KODUJ_H
#define KODUJ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "bit.h"

void compressFile(FILE *inputFile, FILE *outputFile, unsigned int *codes);

#endif // KODUJ_H

