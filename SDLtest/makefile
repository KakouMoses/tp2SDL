CC = gcc # Nom du compilateur
CFLAGS = -Wall -I include # Options de compilation
LDFLAGS = -L lib -lSDL2main -lSDL2 -lmingw32 #-mwindows # Options d'édition de liens

bin/TestSDL.exe : obj/main.o
	$(CC) obj/main.o -o TestSDL.exe $(LDFLAGS)

obj/main.o : src/*.c
	$(CC) $(CFLAGS) -c src/*.c 

# Suppression des fichiers objet
clean:
	rm -rf obj/*.o
# Suppression de tous les fichiers, sauf les sources,
# en vue d’une reconstruction complète.

