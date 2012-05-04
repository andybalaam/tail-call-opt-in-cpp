
DOC_NAME=tail-call-opt-in-cpp

all: display

txt: $(DOC_NAME).txt

html: $(DOC_NAME).html

pdf: $(DOC_NAME).pdf

display: $(DOC_NAME).txt
	less $(DOC_NAME).txt
	rm $(DOC_NAME).txt

zip: txt html pdf
	zip $(DOC_NAME).zip $(DOC_NAME).txt $(DOC_NAME).html $(DOC_NAME).pdf *.svg

stack_bw_dotted.svg:
	cp ../stack_bw_dotted.svg ./stack_bw_dotted.svg

times_bw_dotted.svg:
	cp ../times_bw_dotted.svg ./times_bw_dotted.svg

$(DOC_NAME).txt: $(DOC_NAME).in stack_bw_dotted.svg times_bw_dotted.svg
	m4 $(DOC_NAME).in > $(DOC_NAME).txt || rm $(DOC_NAME).txt

$(DOC_NAME).html: txt
	asciidoc $(DOC_NAME).txt

$(DOC_NAME).xml: txt
	asciidoc -b docbook $(DOC_NAME).txt

$(DOC_NAME).pdf: $(DOC_NAME).xml
	dblatex $(DOC_NAME).xml

clean:
	rm -f $(DOC_NAME).txt $(DOC_NAME).html $(DOC_NAME).pdf


