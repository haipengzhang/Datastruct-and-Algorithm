//
//  CHTbl.h
//  test
//
//  Created by Jimzhang on 2018/1/12.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#ifndef CHTbl_h
#define CHTbl_h

#include <stdio.h>
#include "LinkList.h"

typedef struct CHTbl_
{
    int buckets;
    int (*h)(const void *key);
    int (*match)(const void *key1, const void *key2);
    void (*destroy) (void *data);
    int size;
    List *table;
} CHTbl;

/*Public Interface*/
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));
void chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *htbl, void **data);
int chtbl_lookup(const CHTbl *htbl, void **data);
#define chtbl_size(htbl) ((htbl)->size)
#endif /* CHTbl_h */
