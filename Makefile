# Create by Alexey Romanovets.

bin/MusicSalon: obj/main.o obj/MusicManager.o
	gcc -o bin/MusicSalon.exe obj/main.o obj/MusicManager.o obj/sqlite3.o

obj/main.o: src/main.c
	gcc -c src/main.c -l sqlite3

obj/MusicManager.o: src/MusicManager.c
	gcc -c src/MusicManager.c -l sqlite3

clean:
	rm -rf obj/*.o bin/MusicSalon
