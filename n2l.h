//n2l.h
/*
	Simple wrapper for translating Node ** to List * references
	accepted by my LinkedList library.
*/
#pragma once
#ifndef N2L_H
#define N2L_H

#include "linkedlist.h"

Node * n2l_list_create();

void n2l_list_add(Node ** head, void * data);

void n2l_list_clear(Node ** head);

void * n2l_list_remove(Node ** head, int index);

int n2l_list_indexOf(Node ** head, void * toFind, int (*cmp)(const void * thing1, const void * thing2));

void n2l_list_print(Node ** head, char * (*toString)(void * item));

void n2l_list_destroy(Node ** head);



#endif