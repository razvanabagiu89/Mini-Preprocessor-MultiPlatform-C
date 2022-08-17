build: so-cpp.exe

so-cpp.exe: main.c hashtable.c hashtable.h
	cl /MD /W3 main.c hashtable.c -o so-cpp.exe

clean:
	del so-cpp.exe main.obj hashtable.obj