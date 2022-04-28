#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

typedef struct node node;

typedef struct node
{
    void *obj;
    node *next;
    size_t index;
    bool set;
} node;

typedef node* node_handle;

typedef struct list
{
    size_t objSize;
    node_handle head;
    node_handle tail;
    size_t elementCount;
} list;


static node_handle create_newNode(size_t objSize, void *obj, size_t index);
static int setListItemInternal(list_handle list, void *obj, size_t index, bool updateIfExists);

list_handle list_ctor(size_t elementSize)
{
    list_handle list = (list_handle)malloc(sizeof(list));
    if (list == NULL)
    {
        return list;
    }

    list->objSize = elementSize;
    list->head = NULL;

    return list;
}

void list_dtor(list_handle list)
{
    if (list == NULL)
    {
        return;
    }
    node_handle nodes = list->head;
    while(nodes != NULL)
    {
        node_handle next = nodes->next;
        free(nodes);
        nodes = next;
    }
    free(list);
}

void *list_getItem(list_handle list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }
    node_handle current = list->head;
    while(current->next != NULL && current->index != index);
    {
        current = current->next;
    }
    if (current != NULL || current->index != index)
    {
        return NULL;
    }
    return current->obj;
}

int list_appendItem(list_handle list, void* obj)
{
    if (list == NULL)
    {
        return -1;
    }
    node_handle newNode = create_newNode(list->objSize, obj, list->elementCount + 1);
    if (newNode == NULL)
    {
        return -1;
    }
    list->elementCount++;
    if (list->tail == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    return 0;
}

int list_insertItem(list_handle list, void* obj, size_t index)
{
    return setListItemInternal(list, obj, index, false);
}

int list_setItem(list_handle list, void* obj, size_t index)
{
    return setListItemInternal(list, obj, index, true);
}

static node_handle create_newNode(size_t objSize, void *obj, size_t index)
{
    node_handle newNode = (node_handle)malloc(sizeof(node));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->obj = malloc(objSize);
    if (newNode->obj == NULL)
    {
        return NULL;
    }
    memcpy(newNode->obj, obj, objSize);
    return newNode;
}

static int setListItemInternal(list_handle list, void *obj, size_t index, bool updateIfExists)
{
    if (list == NULL || obj == NULL)
    {
        return -1;
    }
    if (list->head == NULL && updateIfExists == false) // List is empty
    {
        list->head = create_newNode(list->objSize, obj, index);
        list->tail = list->head;
        return list->head != NULL ? 0 : -1;
    }
    
    node_handle current = list->head;
    node_handle lastNode = NULL;
    while(current != NULL && current->index <= index) // && (current->next == NULL || current->next->index < index))
    {
        lastNode = current;
        current = current->next;
    }
    if (current->index == index && updateIfExists == false)
    {
        return -2;
    }
    node_handle newNode = create_newNode(list->objSize, obj, index);
    if (newNode == NULL)
    {
        return -1;
    }
    lastNode->next = newNode;
    if (lastNode == list->tail)
    {
        list->tail = newNode;
    }
    return 0;
}
