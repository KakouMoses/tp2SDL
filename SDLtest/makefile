CC = gcc # Nom du compilateur
CFLAGS = -Wall -I include # Options de compilation
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 # -mwindows # Options d'édition de liens

Programme : TestSDL.exe
	$(CC) main.o -o Programme $(LDFLAGS)

main.o : src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

# Suppression des fichiers temporaires.
clean :
	del -rf *.o

# Suppression de tous les fichiers, sauf les sources,
# en vue d’une reconstruction complète.
mrproper : clean
	del Programme
