#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void sortNodes(HuffNode **nodes, int numNodes) {
    int i, j;
    HuffNode *tmp;

    for (i = 1; i < numNodes; i++) {
        tmp = nodes[i];
        j = i - 1;

        while (j >= 0 && nodes[j]->frequency > tmp->frequency) {
            nodes[j + 1] = nodes[j];
            j--;
        }

        nodes[j + 1] = tmp;
    }
}

HuffNode *createHuffmanTree(int *frequencies) {
    // tworzenie węzłów z częstością wystąpień
    HuffNode **nodes = malloc(sizeof(HuffNode *) * 256);
    int numNodes = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            HuffNode *node = malloc(sizeof(HuffNode));
            node->byte = (unsigned char)i;
            node->frequency = frequencies[i];
            node->left = NULL;
            node->right = NULL;
            nodes[numNodes++] = node;
        }
    }

    // łączenie węzłów w drzewo Huffmana
    while (numNodes > 1) {
        sortNodes(nodes, numNodes);

        HuffNode *left = nodes[0];
        HuffNode *right = nodes[1];

        HuffNode *parent = malloc(sizeof(HuffNode));
        parent->byte = 0;
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;

        nodes[0] = parent;
        nodes[1] = nodes[numNodes - 1];
        numNodes--;
    }

    HuffNode *root = nodes[0];
    free(nodes);

    return root;
}

void freeTree(HuffNode *node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

void writeTree(HuffNode *node, char *str, FILE *out) {

        if (node->left != NULL) {
                strcat(str, "1\0");
                writeTree(node->left, str, out);
        }

        if (node->right != NULL) {
                strcat(str, "0\0");
                writeTree(node->right, str, out);
        }

        if (node->left == NULL && node->right == NULL) {
                fprintf(out, "%d ->%s\n", node->byte, str);
        }

        if (strlen(str) > 0)
                str[strlen(str) - 1] = '\0';
}
