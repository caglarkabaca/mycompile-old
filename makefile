all: compile run

compile:
	gcc -o main main.c parser.c compiler.c structs.c

run:
	./main --compile ./test.mc

clean:
	rm ./main

machine: compile

	./main --machine ./test.mc ./test.mac
