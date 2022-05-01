all: compile run

compile:
	gcc -o main main.c

run:
	./main --compile ./test.mc
