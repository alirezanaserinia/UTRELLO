cc := g++

all: A4.out

A4.out: main.o utrello_interface.o task.o list.o user.o
	$(cc) main.o utrello_interface.o task.o list.o user.o -o A4.out

main.o: main.cpp utrello_interface.hpp
	$(cc) -c main.cpp

utrello_interface.o: utrello_interface.cpp utrello_interface.hpp task.hpp list.hpp user.hpp
	$(cc) -c utrello_interface.cpp

task.o: task.cpp task.hpp
	$(cc) -c task.cpp

list.o: list.cpp list.hpp task.hpp
	$(cc) -c list.cpp

user.o: user.cpp user.hpp task.hpp
	$(cc) -c user.cpp

clean: 
	rm *.o