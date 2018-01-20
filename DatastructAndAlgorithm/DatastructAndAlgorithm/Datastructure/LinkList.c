//
//  LinkList.c
//  test
//
//  Created by Jimzhang on 2018/1/8.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#include "LinkList.h"

#pragma mark - Link list test method

// List和数组一样当作参数传递的时候传的是指针(引用传递)
void list_init(List *list, void(*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    return;
}

void list_destroy(List *list) {
    void *data;
    while (list_size(list) > 0) {
        if (list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(List));
    return;
}

int list_ins_next(List *list, ListElmt *element, const void *data) {
    ListElmt *new_elmt;
    if ((new_elmt = malloc(sizeof(ListElmt))) == NULL) {
        return -1;
    }
    new_elmt->data = (void *)data;
    if (element == NULL) {
        // 插在表头
        if (list_size(list) == 0) list->tail = new_elmt;
        new_elmt->next = list->head;
        list->head = new_elmt;
    } else {
        if (element->next == NULL) list->tail = new_elmt;
        new_elmt->next = element->next;
        element->next = new_elmt;
    }
    list->size++;
    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
    ListElmt *old_elmt;
    if (list_size(list) == 0) {
        return -1;
    }
    if (element == NULL) {
        // 删除表头
        *data = list->head->data;
        old_elmt = list->head;
        list->head = list->head->next;
        if (list_size(list) == 1) list->tail = NULL;
    } else {
        if (element->next == NULL) return -1;
        *data = element->next->data;
        old_elmt = element->next;
        element->next = element->next->next;
        if (element->next == NULL) list->tail = element;
    }
    free(old_elmt);
    list->size--;
    return 0;
}
