
all: test

compile: times_two

times_two: times_two.cpp
	g++ -Wall -Werror -o times_two times_two.cpp

test: compile
	./times_two test

hardware: compile
	./times_two hardware 10

loop: compile
	./times_two loop 10

recursive: compile
	./times_two recursive 10

tail_call: compile
	./times_two tail_call 10


hardware-stack: compile
	./get-stack-usage.sh hardware hardware-stack-usage.txt

loop-stack: compile
	./get-stack-usage.sh loop loop-stack-usage.txt

recursive-stack: compile
	./get-stack-usage.sh recursive recursive-stack-usage.txt

tail_call-stack: compile
	./get-stack-usage.sh tail_call tail_call-usage.txt

hardware-time: compile
	./do-times.sh hardware

loop-time: compile
	./do-times.sh loop

recursive-time: compile
	./do-times.sh recursive

tail_call-time: compile
	./do-times.sh tail_call

