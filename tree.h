#ifndef MAKETREE_H
#define MAKETREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _HuffNode {
    unsigned char byte;
    int frequency;
    struct _HuffNode *left;
    struct _HuffNode *right;
} HuffNode;

void sortNodes(HuffNode **nodes, int numNodes);

HuffNode *createHuffmanTree(int *frequencies, unsigned int *codes);

void writeTreeToFile(HuffNode *node, FILE *file);

void freeTree(HuffNode *node);

void printCodesHelper(HuffNode *node, unsigned int code, int depth, unsigned int *codes);

void printCodes(HuffNode *root, unsigned int *codes);


#endif // MAKETREE_H