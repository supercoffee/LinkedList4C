tester: liblinkedlist test.c
	gcc -Wall -L/opt/lib test.c -llinkedlist -o tester

liblinkedlist: linkedlist.c
	gcc -Wall -fPIC -c linkedlist.c
	gcc -shared -Wl,-soname,liblinkedlist.so.1 -o liblinkedlist.so.1.0   *.o
	cp liblinkedlist.so.1.0 /opt/lib
	ln -sf /opt/lib/liblinkedlist.so.1.0 /opt/lib/liblinkedlist.so.1
	ln -sf /opt/lib/liblinkedlist.so.1.0 /opt/lib/liblinkedlist.so