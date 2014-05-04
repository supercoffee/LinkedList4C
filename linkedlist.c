//
//  linkedlist.c
//  Linked List
//
//  Created by Benjamin Daschel on 3/29/14.
//  Copyright (c) 2014 Benjamin Daschel. All rights reserved.
//

#include "linkedlist.h"

void swap(Node * node1, Node * node2);


List *  list_create(){
    
    List * list  = (List* )calloc(1, sizeof(List));
    
    list -> head = (Node * )calloc(1, sizeof(Node));
    
    list -> head -> next = list -> head;
    list -> head -> prev = list -> head;
    
    return list;

}

void list_clear(List * list){

    Node * head = list -> head;
    
    Node * cur = head -> next;
    while(cur != head){
        
        if(cur -> data != NULL){
            free(cur -> data);
        }
        
        cur = cur -> next;
        
        free(cur -> prev);
        
    }


}

void list_destroy(List * list){
    
    list_clear(list);    

    free(list -> head);
    
    free(list);
    
}


void list_add(List * list, void * data){

    Node * head = list -> head;
 
    Node * newNode = (Node * ) calloc(1, sizeof(Node));

    newNode -> data = data;

    newNode -> next = head;
    newNode -> prev = head -> prev;
    head -> prev -> next = newNode;
    head -> prev = newNode;


}


void list_addFirst(List * list, void * data){

    Node * head = list -> head;
 
    Node * newNode = (Node * ) calloc(1, sizeof(Node));

    newNode -> data = data;

    newNode -> prev = head;
    newNode -> next = head -> next;
    head -> next -> prev = newNode;
    head -> next = newNode;

}

int list_insert(List * list, void * data, const int index){

    if(index >= list_size(list)){
        return 1;
    }

    int i;
    Node * head = list->head;
    Node * cur = head->next;

    for(i = 0; i < index && cur != head; i++, cur = cur->next);

    Node * newNode = (Node * ) calloc(1, sizeof(Node));

    newNode -> data = data;

    newNode -> prev = cur -> prev;
    newNode -> next = cur;
    cur -> prev -> next = newNode;
    cur -> prev = newNode;

    return 0;


}

void list_print(List * list, char * (*toString)(void * item) ){

    Node * head = list -> head;
    Node * cur;

    for(cur = head -> next; cur != head; cur = cur -> next){

        printf("%s, ", toString(cur->data));

    }

}



void * list_get(List * list, int position){

    assert( position < list_size(list));

    Node * head = list -> head;
    Node * cur;


    for(cur = head -> next; position > 0; position--, cur = cur -> next);

    return cur -> data;


}


int list_size(List * list){

    Node * head = list -> head;
    Node * cur;

    int size = 0;

    for(cur = head-> next; cur != head; cur = cur ->next){
        size++;
    }

    return size;

}

void * list_pop(List * list){

    return list_remove(list, list_size(list) - 1);

}


void list_push(List * list, void * data){

    list_addFirst(list, data);

}


void * list_remove(List * list, int position){

    if(position < 0 || position > list_size(list)){
        return NULL;
    }

    Node * head = list -> head;
    Node * cur;

    for(cur = head -> next; position > 0; position--, cur = cur -> next);

    void * data = cur -> data;

    cur -> prev -> next = cur -> next;
    cur -> next -> prev = cur -> prev;

    free(cur);

    return data;

}


void list_enqueue(List * list, void * data){

    list_add(list, data);

}


void * list_dequeue(List * list){

    return list_remove(list, 0);

}

int list_indexOf(List * list, void * tofind, int (*cmp)(const void* thing1, const void* thing2) ){

    Node * head = list -> head;

    Node * cur;

    int index = -1;
    int counter = 0;

    for(cur = head -> next; cur != head; cur = cur -> next){

        if(cmp(tofind, cur->data) == 0){
            index = counter;
            break;
        }

        counter++;
    }

    return index;
}


void list_sort(List * list, int item_size, int(*cmp)(const void * thing1, const void* thing2)){

    int swapped = 1;
    while(swapped){

        Node * cur = list->head->next;
        Node * curNext = cur ->next;

        while(cur->next->data){

            if(cmp(cur->data, curNext->data) > 0){

                swap(cur, curNext);
                swapped = 1;
            }
            else{
                swapped = 0;
            }

            cur = curNext;
            curNext = curNext ->next;


        }


    }

}

void swap(Node * node1, Node * node2){

    void * temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;

}

Iterator * list_iterator(List * list){

    assert( list != NULL);

    Iterator * iter = (Iterator*)calloc(1, sizeof(Iterator));

    iter -> head = list -> head;
    iter -> cur = list -> head;
    iter -> position = -1;

    return iter;
}

void iter_destroy(Iterator * iterator){
    free(iterator);
}

void * iter_next(Iterator * iterator){

    if(iterator -> cur -> next == iterator -> head){
        return NULL;
    }

    iterator -> cur = iterator -> cur -> next;
    iterator->position ++;

    return iterator -> cur -> data;

}

int iter_hasNext(Iterator * iterator){

    if(iterator -> cur -> next == iterator -> head){
        return 0;
    }

    return 1;
}


