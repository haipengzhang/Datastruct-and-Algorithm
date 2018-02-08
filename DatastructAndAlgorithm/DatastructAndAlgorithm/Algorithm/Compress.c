//
//  Compress.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/31.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Compress.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "Bit.h"
#include "PQueue.h"

/* compare_freq */
static int compare_freq(const void *tree1, const void *tree2)
{
    HuffNode *root1, *root2;
    /* compare the frequencues stored in the root nodes of two binary trees */
    root1 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree1));
    root2 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree2));
    if (root1->freq < root2->freq) {
        return 1;
    } else if (root1->freq > root2->freq) {
        return -1;
    } else {
        return 0;
    }
}

/* destroy tree */
static void destroy_tree(void *tree)
{
    /* destroy and free one binary tree from the priority queue of tree */
    bitree_destroy(tree);
    free(tree);
    return;
}

/* build_tree */
static int build_tree(int *freqs, BiTree **tree)
{
    BiTree *init, *merge, *left, *right;
    PQueue pqueue;
    HuffNode *data;
    int size, c;
    
    /* initialize the priority queue of binary trees */
    *tree = NULL;
    pqueue_init(&pqueue, compare_freq, destroy_tree);
    for (c = 0; c <= UCHAR_MAX; c++) {
        if (freqs[c] != 0) {
            /* set up a binary tree for the current symbol and its frequency */
            if ((init = (BiTree *)malloc(sizeof(BiTree))) == NULL) {
                pqueue_destroy(&pqueue);
                return -1;
            }
            bitree_init(init, free);
            if ((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {
                pqueue_destroy(&pqueue);
                return -1;
            }
            data->symbol = c;
            data->freq = freqs[c];
            if (bitree_ins_left(init, NULL, data) != 0) {
                free(data);
                bitree_destroy(init);
                free(init);
                pqueue_destroy(&pqueue);
                return -1;
            }
            /* insert the binary tree into the priority queue */
            if (pqueue_insert(&pqueue, init) != 0) {
                bitree_destroy(init);
                free(init);
                pqueue_destroy(&pqueue);
                return -1;
            }
        }
    }
    /* build a huffman tree by merging trees in the priority queue */
    size = pqueue_size(&pqueue);
    for (c = 1; c <= size - 1; c++) {
        /* allocate storage for the next merged tree */
        if ((merge = (BiTree *)malloc(sizeof(BiTree))) == NULL) {
            pqueue_destroy(&pqueue);
            return -1;
        }
        /* extract the two trees whose root nodes have the smallest frequencies */
        if (pqueue_extract(&pqueue, (void **)&left) != 0) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }
        if (pqueue_extract(&pqueue, (void **)&right) != 0) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }
        /* allocate storage for the data in the root node of the merged tree */
        if ((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }
        memset(data, 0, sizeof(HuffNode));
        
        /* sum the frequencies in the root nodes of the trees being merged */
        data->freq = ((HuffNode *)bitree_data(bitree_root(right)))->freq + ((HuffNode *)bitree_data(bitree_root(left)))->freq;
        /* merge the two trees */
        if (bitree_merge(merge, left, right, data) != 0) {
            pqueue_destroy(&pqueue);
            free(merge);
            return -1;
        }
        /* insert the merged tree into the priority queue and free the others */
        if (pqueue_insert(&pqueue, merge) != 0) {
            pqueue_destroy(&pqueue);
            bitree_destroy(merge);
            free(merge);
            return -1;
        }
        free(left);
        free(right);
    }
    /* the last tree in the priority queue is the huffman tree */
    if (pqueue_extract(&pqueue, (void **)tree) != 0) {
        pqueue_destroy(&pqueue);
        return -1;
    } else {
        pqueue_destroy(&pqueue);
    }
    return 0;
}

/* bulid table */
static void build_table(BiTreeNode *node, unsigned short code, unsigned char size, HuffCode *table)
{
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node))) {
            /* move to the left and append 0 to the current code */
            build_table(bitree_left(node), code << 1, size + 1, table);
        }
        if (!bitree_is_eob(bitree_right(node))) {
            /* move to the right and append 1 to the current code */
            build_table(bitree_right(node), (code << 1) | 0x0001, size + 1, table);
        }
        if (bitree_is_eob(bitree_left(node)) && bitree_is_eob(bitree_right(node))) {
            /* ensure that the current code is in big-endian format */
            code = htons(code);
            /* assign the current code to the symbol in the leaf node */
            table[((HuffNode *)bitree_data(node))->symbol].used = 1;
            table[((HuffNode *)bitree_data(node))->symbol].code = code;
            table[((HuffNode *)bitree_data(node))->symbol].size = size;
        }
    }
    return;
}

/* huffman compress */
int huffman_compress(const unsigned char *original, unsigned char **compressed, int size)
{
    BiTree *tree;
    HuffCode table[UCHAR_MAX + 1];
    int freqs[UCHAR_MAX + 1], max, scale, hsize, ipos, opos, cpos, c, i;
    unsigned char *comp, *temp;
    
    /* initially, there is no buffer of compressed data */
    *compressed = NULL;
    /* get the frequency of each symbol in the original data */
    for (c = 0; c <= UCHAR_MAX; c++) {
        freqs[c] = 0;
    }
    ipos = 0;
    if (size > 0) {
        while (ipos < size) {
            freqs[original[ipos]]++;
            ipos++;
        }
    }
    /* scale the frequencies to fit into one byte */
    max = UCHAR_MAX;
    for (c = 0; c <= UCHAR_MAX; c++) {
        if (freqs[c] > max) {
            max = freqs[c];
        }
    }
    for (c = 0; c <= UCHAR_MAX; c++) {
        scale = (int)(freqs[c] / ((double)max / (double)UCHAR_MAX));
        if (scale == 0 && freqs[c] != 0) {
            freqs[c] = 1;
        } else {
            freqs[c] = scale;
        }
    }
    /* build the huffman tree and table of codes for the data */
    if (build_tree(freqs, &tree) != 0) {
        return -1;
    }
    for (c = 0; c <= UCHAR_MAX; c++) {
        memset(&table[c], 0, sizeof(HuffCode));
    }
    build_table(bitree_root(tree), 0x0000, 0, table);
    bitree_destroy(tree);
    free(tree);
    /* write the header information */
    /* 头四个字节存的是符号数量，后面的256个字节存的是频率（all has scaled，could fit into one byte） */
    hsize = sizeof(int) + (UCHAR_MAX + 1);
    if ((comp = (unsigned char *)malloc(hsize)) == NULL) {
        return -1;
    }
    memcpy(comp, &size, sizeof(int));
    for (c = 0; c <= UCHAR_MAX; c++) {
        comp[sizeof(int) + c] = (unsigned char)freqs[c];
    }
    /*compress the data*/
    ipos = 0;
    opos = hsize * 8;
    while (ipos < size) {
        /* get the next symbol in the original data */
        c = original[ipos];
        for (i = 0; i < table[c].size; i++) {
            if (opos % 8 == 0) {
                /* allocate another byte for the buffer of the compressed data */
                if ((temp = (unsigned char *)realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }
                comp = temp;
            }
            cpos = (sizeof(short) * 8) - table[c].size + i;
            bit_set(comp, opos, bit_get((unsigned char *)&table[c].code, cpos));
            opos++;
        }
        ipos++;
    }
    /* point to the buffer of compressed data */
    *compressed = comp;
    /* return the number of bytes in the compressed data */
    return ((opos - 1) / 8) + 1;
}

/* huffman uncompress */
int huffman_uncompress(const unsigned char *compressed, unsigned char **original)
{
    BiTree *tree;
    BiTreeNode *node;
    int freqs[UCHAR_MAX + 1], hsize, size, ipos, opos, state, c;
    unsigned char *orig, *temp;
    
    /* initially there is no buffer of origin data */
    *original = orig = NULL;
    /* get the header information from the buffer of compressed data */
    hsize = sizeof(int) + (UCHAR_MAX + 1);
    memcpy(&size, compressed, sizeof(int));
    for (c = 0; c <= UCHAR_MAX; c++) {
        freqs[c] = compressed[sizeof(int) + c];
    }
    /* rebuild the huffman tree used previously to compress the data */
    if (build_tree(freqs, &tree) != 0) {
        return -1;
    }
    /* uncompress the data */
    ipos = hsize * 8;
    opos = 0;
    node = bitree_root(tree);
    while (opos < size) {
        /* get the next bit in the compressed data */
        state = bit_get(compressed, ipos);
        ipos++;
        if (state == 0) {
            /* move to the left */
            if (bitree_is_eob(node) || bitree_is_eob(bitree_left(node))) {
                bitree_destroy(tree);
                free(tree);
                return -1;
            } else {
                node = bitree_left(node);
            }
        } else {
            /* move to the right */
            if (bitree_is_eob(node) || bitree_is_eob(bitree_right(node))) {
                bitree_destroy(tree);
                free(tree);
                return -1;
            } else {
                node = bitree_right(node);
            }
        }
        if (bitree_is_eob(bitree_left(node)) && bitree_is_eob(bitree_right(node))) {
            /* write the symbol in the leaf node to the buffer of original data */
            if (opos > 0) {
                if ((temp = (unsigned char *)realloc(orig, opos + 1)) == NULL) {
                    bitree_destroy(tree);
                    free(tree);
                    free(orig);
                    return -1;
                }
                orig = temp;
            } else {
                if ((orig = (unsigned char *)malloc(1)) == NULL) {
                    bitree_destroy(tree);
                    free(tree);
                    return -1;
                }
            }
            orig[opos] = ((HuffNode *)bitree_data(node))->symbol;
            opos++;
            /* move back to the top of the tree */
            node = bitree_root(tree);
        }
    }
    bitree_destroy(tree);
    free(tree);
    /* point to the buffer of original data */
    *original = orig;
    /* return the number of bytes in the original data */
    return opos;
}

/* LZ77 */
/* compare_win */
static int compare_win(const unsigned char *window, const unsigned char *buffer, int *offset, unsigned char *next)
{
    int match, longest, i, j, k;
    /* initialize the offset, although it is valid only once a match is found */
    *offset = 0;
    /* if no match is found, prepare to return 0 and the next symbol in the look-ahead buffer */
    longest = 0;
    *next = buffer[0];
    /* look for the best match in the look-ahead buffer and sliding window */
    for (k = 0; k < L7ZZ_WINDOW_SIZE; k++) {
        i = k;
        j = 0;
        match = 0;
        /* determine how many symbols match in the sliding window at offset k */
        while (i < L7ZZ_WINDOW_SIZE && j < L7ZZ_BUFFER_SIZE - 1) {
            if (window[i] != buffer[j]) {
                break;
            }
            match++;
            i++;
            j++;
        }
        /* keep track of the offset, length, and next symbol for the best match */
        if (match > longest) {
            *offset = k;
            longest = match;
            *next = buffer[j];
        }
    }
    return longest;
}

/* lz77_compress */
int lz77_compress(const unsigned char *original, unsigned char **compressed, int size)
{
    unsigned char window[L7ZZ_WINDOW_SIZE], buffer[L7ZZ_BUFFER_SIZE], *comp, *temp, next;
    int offset, length, remaining, hsize, ipos, opos, tpos, i, token, tbits;
    /* make the pointer to the compressed data not valid until later */
    *compressed = NULL;
    /* write the header information */
    hsize = sizeof(int);
    if ((comp = (unsigned char *)malloc(hsize)) == NULL) {
        return -1;
    }
    memcpy(comp, &size, sizeof(int));
    /* initialize the sliding window and the look-ahead buffer */
    memset(window, 0, L7ZZ_WINDOW_SIZE);
    memset(buffer, 0, L7ZZ_BUFFER_SIZE);
    /* load the look-ahead buffer */
    ipos = 0;
    for (i = 0; i < L7ZZ_BUFFER_SIZE && ipos < size; i++) {
        buffer[i] = original[ipos];
        ipos++;
    }
    /* compress the data */
    opos = hsize * 8;
    remaining = size;
    while (remaining > 0) {
        if ((length = compare_win(window, buffer, &offset, &next)) != 0) {
            /* encode a phrase token */
            token = 0x00000001 << (L7ZZ_PHRASE_BITS - 1);
            /* set the offset where the match was found in the sliding window */
            token = token | (offset << (L7ZZ_PHRASE_BITS - L7ZZ_TYPE_BITS - L7ZZ_WINOFF_BITS));
            /* set the length of the match */
            token = token | (length << (L7ZZ_PHRASE_BITS - L7ZZ_TYPE_BITS - L7ZZ_WINOFF_BITS - L7ZZ_BUFLEN_BITS));
            /* set the next symbol in the look-ahead buffer after the match */
            token = token | next;
            /* set the number of bits in the token */
            tbits = L7ZZ_PHRASE_BITS;
        } else {
            /* encode a symbol token */
            token = 0x00000000;
            /* set the unmatched symbol */
            token = token | next;
            /* set the number of bits in the token */
            tbits = L7ZZ_PHRASE_BITS;
        }
        /* ensure that the token is in big-endian format */
        token = htonl(token);
        /* write the token to the buffer of compressed data */
        for (i = 0; i < tbits; i++) {
            if (opos % 8 == 0) {
                /* allocate another byte for the buffer of compressed data */
                if ((temp = (unsigned char *)realloc(comp, (opos / 8) + 1)) == NULL) {
                    free(comp);
                    return -1;
                }
                comp = temp;
            }
            tpos = (sizeof(unsigned long) * 8) - tbits + 1;
            bit_set(comp, opos, bit_get((unsigned char *)&token, tpos));
            opos++;
        }
        /* adjust the phrase length to account for the unmatched symbol */
        length++;
        /* copy data from the look-ahead buffer to the sliding window */
        memmove(&window[0], &window[length], L7ZZ_WINDOW_SIZE - length);
        memmove(&window[L7ZZ_WINDOW_SIZE - length], &buffer[0], length);
        /* read more data into the look-ahead buffer */
        memmove(&buffer[0], &buffer[length], L7ZZ_BUFFER_SIZE - length);
        for (i = L7ZZ_BUFFER_SIZE - length; i < L7ZZ_BUFFER_SIZE; i++) {
            buffer[i] = original[ipos];
            ipos++;
        }
        /* adjust the total symbols remaining by the phrase length */
        remaining = remaining - length;
    }
    /* point to the buffer of compressed data */
    *compressed = comp;
    /* return the number of bytes in the compressed data */
    return ((opos - 1) / 8) + 1;
}

int lz77_uncompress(const unsigned char *compressed, unsigned char **original);
