#ifndef READTREE_H
#define READTREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readTree.h"

struct ASCII_Code {
    int ascii;
    char binary[1000];
};

int read_file(struct ASCII_Code codes[]);

#endif /* READTREE_H */
