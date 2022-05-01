all: compile run

compile:
	gcc -o main main.c parser.c compiler.c

run:
	./main --compile ./test.mc

clean:
	rm ./main