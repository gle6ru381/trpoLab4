.PHONY: clean
FLAGS=-Wall -Werror -g3
bin/chess: $(patsubst src/%.c,build/src/%.o,$(wildcard src/*.c))
	gcc $^ $(FLAGS) -o $@ 

build/src/%.o: src/%.c
	gcc -o $@ $(FLAGS) -c -MD $<

test: bin/test

bin/test: $(patsubst test/%.c,build/test/%.o,$(wildcard test/*.c)) build/src/board.o build/src/board_print_plain.o build/src/board_read.o
	gcc $^ $(FLAGS) -o $@

build/test/%.o: test/%.c
	gcc -I thirdparty -I src -o $@ $(FLAGS) -c -MD $<

clean:
	rm build/src/*.o
	rm build/src/*.d
	rm build/test/*.o
	rm build/test/*.d

include $(wildcard build/*.d)