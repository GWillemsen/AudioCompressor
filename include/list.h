#pragma once
#ifndef AUDIOCOMPRESSOR_LIST_H
#define AUDIOCOMPRESSOR_LIST_H
#include <stdlib.h>

typedef struct list list;

typedef list* list_handle;

list_handle list_ctor(size_t elementSize);

void list_dtor(list_handle list);

void *list_getItem(list_handle list, size_t index);

int list_appendItem(list_handle list, void* obj);

int list_insertItem(list_handle list, void* obj, size_t index);

int list_setItem(list_handle list, void* obj, size_t index);

#endif // AUDIOCOMPRESSOR_LIST_H