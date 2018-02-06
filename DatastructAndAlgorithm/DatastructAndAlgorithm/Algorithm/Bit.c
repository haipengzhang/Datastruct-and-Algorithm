//
//  Bit.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/31.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Bit.h"
#include <string.h>

//给定一个字符串二进制序列，取pos位数据，低位在前高位在后（小端模式）
int bit_get(const unsigned char *bits, int pos)
{
    unsigned char mask;
    int i;
    /* Set a mask for the bit to get */
    mask = 0x80;
    for (i = 0; i < (pos % 8); i++) {
        mask = mask >> 1; //right shift
    }
    /* get the bit */
    return (((mask & bits[(int)(pos / 8)]) == mask) ? 1 : 0);
}

void bit_set(unsigned char *bits, int pos, int state)
{
    unsigned char mask;
    int i;
    /* Set a mask for the bit to get */
    mask = 0x80;
    for (i = 0; i < (pos % 8); i++) {
        mask = mask >> 1;
    }
    /* Set the bit */
    if (state) {
        bits[pos / 8] = bits[pos / 8] | mask;
    } else {
        bits[pos / 8] = bits[pos / 8] & (~mask);
    }
    return;
}

void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size)
{
    int i;
    /* compute the bitwise xor (exclusive or) of the two buffers */
    for (i = 0; i < size; i++) {
        if (bit_get(bits1, i) != bit_get(bits2, i)) {
            bit_set(bitsx, i, 1);
        } else {
            bit_set(bitsx, i, 0);
        }
    }
    return;
}

void bit_rot_left(unsigned char *bits, int size, int count)
{
    int fbit, lbit, i, j;
    /* rotate the buffer to the left the specified number of bits */
    if (size > 0) {
        for (j = 0; j < count; j++) {
            for (i = 0; i <= ((size -1) / 8); i++) {
                /* get the bit about to be shifed off the current byte */
                lbit = bit_get(&bits[i], 0);
                if (i == 0) {
                    /* save the bit about to be shifed off the current byte */
                    fbit = lbit;
                } else {
                    /* set the rightmost bit of the previous byte to the leftmost
                     * bit about to be shifed off the current byte
                     */
                    bit_set(&bits[i - 1], 7, lbit);
                }
                /* shifted the current byte to the left */
                bits[i] = bits[i] << 1;
            }
            /* set the rightmost bit of the buffer to the bit shifted off the first byte */
            bit_set(bits, size - 1, fbit);
        }
    }
    return;
}


