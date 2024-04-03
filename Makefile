# Create by Alexey Romanovets.

bin/MusicSalon: obj/main.o obj/MusicManager.o obj/sqlite3.o
	gcc -o bin/MusicSalon.exe obj/main.o obj/MusicManager.o obj/sqlite3.o

obj/main.o: src/main.c
	gcc -c src/main.c

obj/MusicManager.o: src/MusicManager.c
	gcc -c src/MusicManager.c

obj/sqlite3.o: sqlite/sqlite3.c
	gcc -c sqlite/sqlite3.c

clean:
	rm -rf obj/*.o bin/MusicSalon
