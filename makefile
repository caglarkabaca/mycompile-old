all: gcc7

gcc11: compile11 run

gcc7: compile7 run

compile11:
	gcc-11 -std=c99 -g -o main main.c parser.c compiler.c structs.c

compile7:
	gcc-7 -std=c99 -g -o main main.c parser.c compiler.c structs.c

run:
	./main --compile ./test.mc


clean:
	rm ./main

machine: compile

	./main --machine ./test.mc ./test.mac
