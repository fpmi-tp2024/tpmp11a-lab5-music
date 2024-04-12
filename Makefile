# Create by Alexey Romanovets.
# Changed by kirill now it's good makefile best of the best one love i compiled the project yeeaahhh

test: test/test
    ./test/test
    git restore db

test/test: test/test.o
    g++ -std=c++20 -o test/test test/test.o -l sqlite3 -l gtest -l gtest_main

test/test.o: test/test.cpp
    g++ -std=c++20 -o test/test.o -c test.cpp

bin/MusicSalon: obj/main.o obj/MusicManager.o obj/sqlite3.o
	gcc -o bin/MusicSalon obj/main.o obj/MusicManager.o obj/sqlite3.o

obj/main.o: src/main.c
	gcc -o obj/main.o -c src/main.c

obj/MusicManager.o: src/MusicManager.c
	gcc -o obj/MusicManager.o -c src/MusicManager.c

obj/sqlite3.o: sqlite/sqlite3.c
	gcc -o obj/sqlite3.o -c sqlite/sqlite3.c

clean:
	rm -rf obj/*.o bin/MusicSalon test/*.o test/test

check: 
	shell: /usr/bin/bash -e {0}

distcheck:
	shell: /usr/bin/bash -e {0}
