CC     = gcc
FLEX   = flex
BISON  = bison -d -v
SRC    = src

all: draft

draft: $(SRC)/draft.l $(SRC)/draft.y
	$(BISON) -o $(SRC)/draft.tab.c $(SRC)/draft.y
	$(FLEX)  -o $(SRC)/lex.yy.c     $(SRC)/draft.l
	$(CC) -o draft $(SRC)/lex.yy.c $(SRC)/draft.tab.c -lfl

run: draft
	./draft < examples/exemplo.dft   # ou make run ARQ=...

clean:
	rm -f draft $(SRC)/lex.yy.c $(SRC)/draft.tab.* $(SRC)/draft.output

.PHONY: all run clean
