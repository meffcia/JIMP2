#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readTree.h"

void encode_file(struct ASCII_Code codes[], FILE *in, FILE *out);

#endif /* COMPRESS_H */
