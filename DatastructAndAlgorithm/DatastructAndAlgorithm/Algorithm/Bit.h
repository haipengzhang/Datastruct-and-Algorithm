//
//  Bit.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/31.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Bit_h
#define Bit_h

#include <stdio.h>

int bit_get(const unsigned char *bits, int pos);
void bit_set(unsigned char *bits, int pos, int state);
void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size);
void bit_rot_left(unsigned char *bits, int size, int count);

#endif /* Bit_h */
