#include <stdio.h>
#include <stdlib.h>
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

HuffNode *createHuffmanTree(int *frequencies, unsigned int *codes) {
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

            // dodawanie kodu do tablicy kodów
            codes[i] = 0;
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

void writeTreeToFile(HuffNode *node, FILE *file) {
    // zapis drzewa w pliku
    if (node->left == NULL && node->right == NULL) {
        fputc('1', file);
        fputc(node->byte, file);
    } else {
        fputc('0', file);
        writeTreeToFile(node->left, file);
        writeTreeToFile(node->right, file);
    }
}

void printCodesHelper(HuffNode *node, unsigned int code, int depth, unsigned int *codes) {
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        // zapis kodu w tablicy kodów
        codes[node->byte] = code;
    } else {
        printCodesHelper(node->left, (code << 1) | 0, depth + 1, codes);
	printCodesHelper(node->right, (code << 1) | 1, depth + 1, codes);
    }
}
void printCodes(HuffNode *root, unsigned int *codes) {
	// wywołanie rekurencyjnej funkcji pomocniczej
	printCodesHelper(root, 0, 0, codes);
}

