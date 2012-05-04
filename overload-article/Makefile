
DOC_NAME=tail-call-opt-in-cpp

all: display

html: $(DOC_NAME).html

pdf: $(DOC_NAME).pdf

display: $(DOC_NAME).txt
	less $(DOC_NAME).txt
	rm $(DOC_NAME).txt

stack.svg:
	cp ../stack_bw_dotted.svg ./stack_bw_dotted.svg

times.svg:
	cp ../times_bw_dotted.svg ./times_bw_dotted.svg

$(DOC_NAME).txt: $(DOC_NAME).in stack.svg times.svg
	m4 $(DOC_NAME).in > $(DOC_NAME).txt || rm $(DOC_NAME).txt

$(DOC_NAME).html: $(DOC_NAME).txt
	asciidoc $(DOC_NAME).txt

$(DOC_NAME).xml: $(DOC_NAME).txt
	asciidoc -b docbook $(DOC_NAME).txt

$(DOC_NAME).pdf: $(DOC_NAME).xml
	dblatex $(DOC_NAME).xml

clean:
	rm -f $(DOC_NAME).txt


