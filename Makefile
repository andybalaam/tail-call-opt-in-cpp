
TIMES=times-hardware.txt times-loop.txt times-recursive.txt times-tail_call.txt
STACKS=stack-hardware.txt stack-loop.txt stack-recursive.txt stack-tail_call.txt

all: test

times_two: times_two.cpp
	g++ -Wall -Werror -o times_two times_two.cpp

test: compile
	./times_two test

hardware: times_two
	./times_two hardware 10

loop: times_two
	./times_two loop 10

recursive: times_two
	./times_two recursive 10

tail_call: times_two
	./times_two tail_call 10


stack-view: stack.svg
	firefox stack.svg

stack.svg: plot_stack.gnuplot $(STACKS)
	gnuplot plot_stack.gnuplot

stack: $(STACKS)

stack-%.txt: times_two Makefile do-stack.sh
	./do-stack.sh $* > $@

clean-stack:
	rm -f $(STACKS)



times-view: times.svg
	firefox times.svg

times.svg: plot_times.gnuplot $(TIMES)
	gnuplot plot_times.gnuplot

times: $(TIMES)

times-%.txt: times_two Makefile do-times.sh
	./do-times.sh $* > $@

clean-times:
	rm -f $(TIMES)

