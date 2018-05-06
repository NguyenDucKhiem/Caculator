#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>

struct List{
    char *item;
    List *next;
    List *pre;
};

List *InitList(char *item){
    List *l = (List *) malloc(sizeof(List));
    if (l == NULL) return NULL;
    l->item = item;
    l->next = NULL;
    l->pre = NULL;
    return l;
}

struct LinkedList{
    List *Head;
    List *Bottom;
};

LinkedList *InitLinkedList(){
    LinkedList *link = (LinkedList *) malloc(sizeof(LinkedList));
    link->Head = NULL;
    link->Bottom = NULL;
    return link;
}

void AddToHeadLL(LinkedList *link, char *item){
    if (link == NULL) return;
    if (link->Head == NULL){
        List *node = InitList(item);
        link->Head = node;
        link->Bottom = node;
        return;
    }
    List *l = InitList(item);
    if (l == NULL) return;
    link->Head->pre = l;
    l->next = link->Head;
    link->Head = l;
    return;
}

void AddToBottomLL(LinkedList *link, char *item){
    if (link == NULL) return;
    if (link->Head == NULL){
        List *node = InitList(item);
        link->Head = node;
        link->Bottom = node;
        return;
    }
    List *l = InitList(item);
    if (l == NULL) return;
    List *node = link->Bottom;
    l->pre = node;
    node->next = l;
    link->Bottom = l;
    return;
}

char *DeleteToHeadLL(LinkedList *link){
    if (link->Head == NULL) return NULL;
    List *node = link->Head;
    link->Head = node->next;
    link->Head->pre = NULL;
    char *item = node->item;
    free(node);
    return item;
}

char *DeleteToBottomLL(LinkedList *link){
    if (link->Head == NULL) return NULL;
    List *node = link->Bottom;
    if (node->pre == NULL){
        link->Bottom = NULL;
        link->Head = NULL;
    } else {
        link->Bottom = node->pre;
        link->Bottom->next = NULL;
    }

    char *item = node->item;
    free(node);
    return item;
}

void FreeLinkedList(LinkedList *link){
    while (link->Head != NULL) DeleteToHeadLL(link);
    free(link);
}

void printLinkedList(LinkedList *link){
    if (link == NULL) {
        printf("Error");
        return;
    }

    if (link->Head == NULL) {
        printf("None");
        return;
    }
    List *l = link->Head;
    while (l != NULL){
        printf("%s ", l->item);
        l = l->next;
    }
}

#endif // LINKEDLIST_H_INCLUDED
