//
//  main.m
//  test
//
//  Created by Jimzhang on 2018/1/4.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "CPointer.h"

int main(int argc, char * argv[]) {
    @autoreleasepool {
        // c pointer test
        int a = 100;
        int b = 200;
        swap(&a, &b);
        printf("a=%i==b=%i\n", a, b);
        swap2(&a, &b, sizeof(int));
        printf("a=%i==b=%i\n", a, b);
        
        // 悬空指针
        int *iptr;
        f(&iptr);
        printf("f=%i\n", *iptr);
        
        // 动态内存分配
        g(&iptr);
    }
}
