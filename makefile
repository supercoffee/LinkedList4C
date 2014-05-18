tester: linkedlist.c test.c
	gcc -g linkedlist.c test.c -lrt -o tester

liblinkedlist: linkedlist.c
	gcc -Wall -fPIC -c linkedlist.c
	gcc -shared -Wl,-soname,liblinkedlist.so.1 -o liblinkedlist.so.1.0   *.o
	sudo cp liblinkedlist.so.1.0 /opt/lib
	sudo ln -sf /opt/lib/liblinkedlist.so.1.0 /opt/lib/liblinkedlist.so.1
	sudo ln -sf /opt/lib/liblinkedlist.so.1.0 /opt/lib/liblinkedlist.so