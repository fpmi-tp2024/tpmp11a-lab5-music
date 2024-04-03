# Create by Alexey Romanovets.

bin/MusicSalon: obj/main.o obj/MusicManager.o
	gcc -o bin/MusicSalon.exe obj/main.o obj/MusicManager.o obj/sqlite3.o sqlite/sqlite3.c

obj/main.o: src/main.c
	gcc -c src/main.c

obj/MusicManager.o: src/MusicManager.c
	gcc -c src/MusicManager.c

clean:
	rm -rf obj/*.o bin/MusicSalon
