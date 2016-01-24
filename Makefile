all:
	gcc -o manini src/main.c src/minIni/dev/minIni.c -I src/minIni/dev/

clean:
	rm manini
