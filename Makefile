
TIMES=times-hardware.txt times-loop.txt times-recursive.txt times-tail_call.txt
STACKS=stack-hardware.txt stack-loop.txt stack-recursive.txt stack-tail_call.txt

SOURCES=times_two.cpp test_one.cpp hardware.cpp loop.cpp recursive.cpp tail_call.cpp tail_call_templ.cpp

all: test

times_two: $(SOURCES)
	g++ -Wall -Werror -o times_two times_two.cpp

test: times_two
	./times_two test



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

