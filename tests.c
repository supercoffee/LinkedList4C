//
// Created by Benjamin Daschel on 4/3/18.
//

#include "tests.h"
#include "linkedlist.h"
#include "Unity-2.4.3/src/unity.h"

List * theList;

void setUp(void) {
    theList = list_create();
}

void tearDown() {
    list_destroy(&theList);
}

void test_list_created() {
    TEST_ASSERT(theList != NULL);
}

void test_list_teardown() {
    list_destroy(&theList);
    TEST_ASSERT(theList == NULL);
}

void test_list_add() {
    int * element = (int*) malloc(sizeof(int));
    *element = 42;
    list_add(theList, element);
    TEST_ASSERT(*(int*)(list_get(theList, 0)) == 42);
}

void test_list_clear() {
    int * element = (int*) malloc(sizeof(int));
    *element = 42;
    list_add(theList, element);
    list_clear(theList);
    TEST_ASSERT(theList->head->next == theList->head->prev);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_created);
    RUN_TEST(test_list_teardown);
    RUN_TEST(test_list_add);
    RUN_TEST(test_list_clear);
    return UNITY_END();
}