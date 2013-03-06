all: project-execute

SQLite-build: sqlite3.h sqlite3.c
	gcc -c sqlite3.c

project-execute: execute.cpp sqlite3.o
	g++ -o prog execute.cpp sqlite3.o

clean:
	del *.o *.exe *.db