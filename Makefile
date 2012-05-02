
DOC_NAME=tail-call-opt-in-cpp

TIMES=times-hardware.txt times-loop.txt times-recursive.txt times-tail_call.txt
STACKS=stack-hardware.txt stack-loop.txt stack-recursive.txt stack-tail_call.txt

all: test display



html: $(DOC_NAME).html

pdf: $(DOC_NAME).pdf

display:
	less $(DOC_NAME).txt
	rm $(DOC_NAME).txt

$(DOC_NAME).txt: $(DOC_NAME).in
	m4 $(DOC_NAME).in > $(DOC_NAME).txt || rm $(DOC_NAME).txt

$(DOC_NAME).html: $(DOC_NAME).txt
	asciidoc $(DOC_NAME).txt

$(DOC_NAME).xml: $(DOC_NAME).txt
	asciidoc -b docbook $(DOC_NAME).txt

$(DOC_NAME).pdf: $(DOC_NAME).xml
	dblatex $(DOC_NAME).xml

clean:
	rm -f $(DOC_NAME).txt



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

