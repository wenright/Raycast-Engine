all:
	gcc -std=c99 -o run src/*.c -lSDL2 -lSDL2_ttf -lm -g
clean:
	rm run