//
//  Compress.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/31.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Compress_h
#define Compress_h
#include "BiTree.h"
#include <stdio.h>

/* define a structure for nodes of huffman trees */
typedef struct HuffNode_ {
    unsigned char symbol;
    int freq;
} HuffNode;

/* Define a structure for entries Huffman code tables */
typedef struct HuffCode_{
    unsigned char used;
    unsigned short code;
    unsigned char size;
} HuffCode;

/* define the number of bits required for LZ77 token members */
#define L7ZZ_TYPE_BITS      1
#define L7ZZ_WINOFF_BITS    12
#define L7ZZ_BUFLEN_BITS    5
#define L7ZZ_NEXT_BITS      8

/* define the size of the sliding window and the look-ahead buffer for
 * LZ77. Each must be less than or equel to 2 raised to L7ZZ_WINOFF_BITS
 * and LZ77_BUFLEN_BITS respectively
 */
#define L7ZZ_WINDOW_SIZE    4096
#define L7ZZ_BUFFER_SIZE    32

/* define the number of bits for LZ77 phrase tokens */
#define L7ZZ_PHRASE_BITS    (L7ZZ_TYPE_BITS + L7ZZ_WINOFF_BITS + L7ZZ_NEXT_BITS + L7ZZ_BUFLEN_BITS)
/* define the number of bits for LZ77 symbol tokens */
#define L7ZZ_SYMBOL_BITS    (L7ZZ_TYPE_BITS + L7ZZ_NEXT_BITS)

/* public interface */
int huffman_compress(const unsigned char *original, unsigned char **compressed, int size);
int huffman_uncompress(const unsigned char *compressed, unsigned char **original);
int lz77_compress(const unsigned char *original, unsigned char **compressed, int size);
int lz77_uncompress(const unsigned char *compressed, unsigned char **original);

#endif /* Compress_h */
