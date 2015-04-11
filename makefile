EXE=hello

link: compile
	gcc -o $(EXE) *.o

compile:
	gcc -g -c *.c
clean:
	rm $(EXE) *.o


