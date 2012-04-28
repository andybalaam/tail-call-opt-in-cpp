
TIMES=times-hardware.txt times-loop.txt times-recursive.txt times-tail_call.txt

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


hardware-stack-usage.txt: times_two
	./get-stack-usage.sh hardware >@

loop-stack-usage.txt: times_two
	./get-stack-usage.sh loop > $@

recursive-stack-usage.txt: times_two
	./get-stack-usage.sh recursive > $@

tail_call-usage.txt: times_two
	./get-stack-usage.sh tail_call > $@



times-view:
	gnuplot plot_times.gnuplot -persist

times:$(TIMES)

times-hardware.txt: times_two Makefile do-times.sh
	./do-times.sh hardware > $@

times-loop.txt: times_two Makefile do-times.sh
	./do-times.sh loop > $@

times-recursive.txt: times_two Makefile do-times.sh
	./do-times.sh recursive > $@

times-tail_call.txt: times_two Makefile do-times.sh
	./do-times.sh tail_call > $@

clean-times:
	rm -f $(TIMES)
