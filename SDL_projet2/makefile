CC = gcc # Nom du compilateur
CFLAGS = -Wall -I include # Options de compilation
LDFLAGS = -L lib -lSDL2main -lSDL2  # Options d'édition de liens
WLDFLAGS = -L lib -lSDL2main -lSDL2 -lmingw32 -mwindows
# Là on va devoir mettre beaucoup de paramètres pour ne pas se retrouver confus
EXE_DIR = bin
OBJ_DIR = obj


bin/TestSDL.exe : main.o
	$(CC) main.o -o TestSDL.exe $(LDFLAGS)

obj/main.o : src/*.c
	$(CC) $(CFLAGS) -c src/*.c -o main.o

# Suppression des fichiers objet
clean:
	rm -f obj/*.o
# Suppression de tous les fichiers, sauf les sources,
# en vue d’une reconstruction complète.

