//
//  linkedlist.h
//  Linked List
//
//  Created by Benjamin Daschel on 3/29/14.
//  Copyright (c) 2014 Benjamin Daschel. All rights reserved.
//
#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node Node;

//used internally by the list
struct node{
    
    Node * next;
    void * data;
    Node * prev;
    
};

typedef struct{
    //this head node is a dummy;
    Node * head;

    int* length;
    
} List;

/*
    Creates an empty list.
 */
List *  list_create();

/*
 Clean up an existing list including all of the
 referenced content in the list. 
*/
void list_destroy(List * list);


/*
	Removes all elements from the list, but leaves the list
	available to be used again. 
*/
void list_clear(List * list);


/*
	Add an element to the list at the end
*/
void list_add(List * list, void * data);

/*
	Add an element to the beginning of the list.
*/
void list_addFirst(List * list, void * data);

/*
    Print the contents of the list data.
    Preferably only use with char* data type,
    otherwise you'll get garbage.  
*/
void list_print(List * list, char * (*toString)(void * item) );


/*
	Retrieve the item at the give position in the list.
*/
void * list_get(List * list, int position);

/*
	Get the size of the list in terms of elements
*/
int list_size(List * list);

/*
	Pop the first item from the stack. 
	Becuase this function returns the data element,
	the data element must be freed by the caller. 
*/
void * list_pop(List * list);

/*
	Push an item onto the stack.
*/
void list_push(List * list, void * data);

/*
	Remove an item from the list.

	This function will not free the data element 
	at the specified position. The caller of this
	function will need to free the returned data. 
*/
void * list_remove(List * list, int position);


/*
	Find an element in the list using the *cmp function to compare
	elements with the element to find. 
*/
int list_indexOf(List * list, void * tofind, int (*cmp)(const void* thing1, const void* thing2) );

/*
	Enqueue an item into the queue.
*/
void list_enqueue(List * list, void * data);

/*
	Dequeue an item from the queue;
*/
void * list_dequeue(List * list);

/*
	Sort a linked list in place using a crappy sorting method. **Cough bubblesort *cough
*/
void list_sort(List * list, int item_size, int(*cmp)(const void * thing1, const void* thing2) );



#endif
