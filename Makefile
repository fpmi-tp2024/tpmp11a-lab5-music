# Create by Alexey Romanovets.
# Changed by kirill now it's good makefile best of the best one love i compiled the project yeeaahhh

bin/MusicSalon: obj/main.o obj/MusicManager.o obj/sqlite3.o
	gcc -o bin/MusicSalon obj/main.o obj/MusicManager.o obj/sqlite3.o

obj/main.o: src/main.c
	gcc -o obj/main.o -c src/main.c

obj/MusicManager.o: src/MusicManager.c
	gcc -o obj/MusicManager.o -c src/MusicManager.c

obj/sqlite3.o: sqlite/sqlite3.c
	gcc -o obj/sqlite3.o -c sqlite/sqlite3.c

clean:
	rm -rf obj/*.o bin/MusicSalon

check: 
	shell: /usr/bin/bash -e {0}

distcheck:
	shell: /usr/bin/bash -e {0}
