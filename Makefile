all:
	gcc -std=c99 -o run src/*.c -g -lSDL2 -lm
clean:
	rm run