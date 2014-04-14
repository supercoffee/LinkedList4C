//n2l.c

#include "n2l.h"

Node * n2l_list_create(){

	Node * head = (Node *)calloc(1, sizeof(Node));

	head -> next = head;
	head -> prev = head;

	return head;
}

void n2l_list_add(Node ** head, void * data){

		List * list  = (List * )calloc(1, sizeof(List));

		list -> head = *head;

		list_add(list, data);

		free(list);

}

void n2l_list_clear(Node ** head){

	List * list = (List * )calloc(1, sizeof(list));

	list->head = *head;

	list_clear(list);

	free(list);

}

void * n2l_list_remove(Node ** head, int index){

	List * list = (List *) calloc(1, sizeof(List));

	list -> head = * head;

	void * removed = list_remove(list, index);

	free(list);

	return removed;
}

int n2l_list_indexOf(Node ** head, void * toFind, int (*cmp)(const void * thing1, const void * thing2)){

	List * list = (List *) calloc(1, sizeof(List));

	list -> head = * head;

	int index = list_indexOf(list, toFind, cmp);

	free(list);

	return index;

}

void n2l_list_print(Node ** head, char * (*toString)(void * item)){
	List * list = (List* )calloc(1, sizeof(List));

	list->head = *head;

	list_print(list, toString);

	free(list);

}

void n2l_list_destroy(Node ** head){

	List * list = (List *)calloc(1, sizeof(List));

	list -> head = * head;

	list_destroy(list);

}

void n2l_list_sort(Node ** head, int item_size, int(*cmp)( const void * thing1, const void* thing2) ){

	List * list = (List *)calloc(1, sizeof(List));

	list ->head = *head;

	list_sort(list, item_size, cmp);

	free(list);

}




