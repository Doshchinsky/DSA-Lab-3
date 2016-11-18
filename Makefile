INCLUDES = -I src/
dirs = ./bin ./obj
main_obj = ./obj/fh_main.o ./obj/fh_lib.o

all: ./bin/fh_main

./bin/fh_main: $(dirs) $(main_obj)
	gcc $(main_obj) -Wall -o ./bin/fh_main -lm

$(dirs):
	mkdir obj
	mkdir bin

./obj/fh_main.o: ./src/fh_main.c
	gcc -c ./src/fh_main.c -Wall -o ./obj/fh_main.o $(INCLUDES)

./obj/fh_lib.o: ./src/fh_lib.c
	gcc -c ./src/fh_lib.c -Wall -o ./obj/fh_lib.o $(INCLUDES)

.PHONY: clean
clean:
	rm -rf bin/ obj/