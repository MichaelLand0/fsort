exec = fsort.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

#install:
#	make
#	cp ./fsort.out /usr/local/bin/fsort


clean:
	-rm *.out
	-rm src/*.o
