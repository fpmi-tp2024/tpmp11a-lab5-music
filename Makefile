# Create by Alexey Romanovets.

bin/MusicSalon: obj/main.o obj/MusicManager.o obj/sqlite3.o
	gcc -o bin/MusicSalon.exe obj/main.o obj/MusicManager.o obj/sqlite3.o

obj/main.o: src/main.c
	gcc -c src/main.c
	move main.o obj

obj/MusicManager.o: src/MusicManager.c
	gcc -c src/MusicManager.c
	move MusicManager.o obj

obj/sqlite3.o: sqlite/sqlite3.c
	gcc -c sqlite/sqlite3.c
	move sqlite3.o obj

clean:
	rm -rf obj/*.o bin/MusicSalon
