liblinkedlist: linkedlist.c
	mkdir -p build
	gcc -Wall -g -fPIC -c linkedlist.c -o build/liblinkedlist.o

tests: liblinkedlist tests.c
	gcc -Wall -g build/liblinkedlist.o Unity-2.4.3/src/unity.c tests.c -o testrunner

valgrind_tests: tests
	valgrind --leak-check=full --track-origins=yes ./testrunner

