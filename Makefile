all:
	gcc -std=c99 -o run src/*.c -g -lSDL2 -lSDL2_ttf -lm
clean:
	rm run