//
//  linkedlist.c
//  Linked List
//
//  Created by Benjamin Daschel on 3/29/14.
//  Copyright (c) 2014 Benjamin Daschel. All rights reserved.
//

#include "linkedlist.h"

#define RECYCLE 1

//used internally by the list
struct node_t{
    
    Node * next;
    void * data;
    Node * prev;
    
};

struct list_t{
    //this head node is a dummy;
    Node * head;

    int size;

    /*
        A chain of empty nodes whose previous
        contents have been removed from the list.
        Holding onto these references will save time
        in allocating new nodes as these will be reused first. 
    */
    Node * recycle;
};

/*
    position denotes the index of the node referenced
    by cur. If no data has been read from the iterator, 
    then position will be -1. 
*/
struct iter_t {
    Node * head;
    Node * cur;
    List * list;
    int position;
};

void swap(Node * node1, Node * node2);
void recycle(Node * node, List * list);


List *  list_create(){
    
    List * list  = (List* )calloc(1, sizeof(List));
    
    list -> head = (Node * )calloc(1, sizeof(Node));
    
    list -> head -> next = list -> head;
    list -> head -> prev = list -> head;

    list -> size = 0;

    list -> recycle = NULL;
    
    return list;

}

void list_clear(List * list){

    Node * head = list -> head;
    
    Node * cur = head -> next;
    Node * next;
    while(cur != head){
        next = cur -> next;

        if(cur -> data != NULL){
            free(cur -> data);
            cur->data = NULL;
        }

        recycle(cur, list);
        
        cur = next;
    }


    head -> prev = head;
    head -> next = head;

    list -> size = 0;

}

void list_destroy(List * list){
    
    list_clear(list);    

    if(list->recycle){
        Node * recycle = list-> recycle;
        while(recycle){
            Node * next = recycle -> next;
            free(recycle);
            recycle = next;
        }
    }

    free(list -> head);
    
    free(list);
    
}


void list_add(List * list, void * data){

    Node * head = list -> head;
    Node * newNode;

    if(list->recycle){
        newNode = list->recycle;
        list->recycle = newNode->next;
    }else{
        newNode = (Node * ) calloc(1, sizeof(Node));   
    }

    newNode -> data = data;

    newNode -> next = head;
    newNode -> prev = head -> prev;
    head -> prev -> next = newNode;
    head -> prev = newNode;

    list -> size++;


}


void list_addFirst(List * list, void * data){

    Node * head = list -> head;
    Node * newNode;

    if(list->recycle){
        newNode = list->recycle;
        list->recycle = newNode->next;
    }else{
        newNode = (Node * ) calloc(1, sizeof(Node));   
    }

    newNode -> data = data;

    newNode -> prev = head;
    newNode -> next = head -> next;
    head -> next -> prev = newNode;
    head -> next = newNode;

    list -> size++;

}

int list_insert(List * list, void * data, const int index){

    if(index >= list_size(list) ){
        return 1;
    }

    int i;
    Node * head = list->head;
    Node * cur = head->next;

    for(i = 0; i < index && cur != head; i++, cur = cur->next);

    Node * newNode;

    if(list->recycle){
        newNode = list->recycle;
        list->recycle = newNode->next;
    }else{
        newNode = (Node * ) calloc(1, sizeof(Node));   
    }

    newNode -> data = data;

    newNode -> prev = cur -> prev;
    newNode -> next = cur;
    cur -> prev -> next = newNode;
    cur -> prev = newNode;

    list -> size++;

    return 0;


}

void list_print(List * list, char * (*toString)(void * item) ){

    Node * head = list -> head;
    Node * cur;

    for(cur = head -> next; cur != head; cur = cur -> next){

        printf("%s, ", toString(cur->data));

    }

    printf("\n");

}



void * list_get(List * list, int position){

    assert( position < list_size(list));

    Node * head = list -> head;
    Node * cur;


    for(cur = head -> next; position > 0; position--, cur = cur -> next);

    return cur -> data;


}


int list_size(List * list){

    return list -> size;

}

void * list_pop(List * list){

    if(list_size(list) < 1){
        return NULL;
    }

    Node * head = list -> head;
    Node * cur = head -> prev;
    void * data = cur -> data;

    head -> prev = cur -> prev;
    cur -> prev -> next = head;

    recycle(cur, list);

    list -> size--;

    return data;
}


void list_push(List * list, void * data){

    list_add(list, data);

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

    recycle(cur, list);

    list -> size--;

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
    iter -> list = list;
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

void * iter_remove(Iterator * iterator){

    Node * cur = iterator -> cur;
    List * list = iterator->list;
    void * result = NULL;

    if(cur == iterator -> head){
        return NULL;
    }
    result =  cur -> data;
    cur -> data = NULL;

    cur->next->prev = cur -> prev;
    cur->prev->next = cur -> next;

    list->size--;

    // move to previous because iter_next
    // advanced the cursor before reading data
    iterator -> cur = cur->next;
 
    recycle(cur, list);

    return result;
}

void iter_reset(Iterator * iterator){

    List * list = iterator -> list;
    iterator -> head = list -> head;
    iterator -> cur = list -> head;
    iterator -> position = -1;
}

void recycle(Node * node, List * list){

    #if RECYCLE

    node->prev = NULL;
    node->data = NULL;
    if(list->recycle == NULL){
        node->next = NULL;
    }
    else{
        node->next = list->recycle;
    }

    list->recycle = node;
    #else

    free(node);

    #endif

}
