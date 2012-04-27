
all: test

compile: times_two

times_two: times_two.cpp
	g++ -Wall -Werror -o times_two times_two.cpp

test: compile
	./times_two test

hardware: compile
	./times_two hardware


