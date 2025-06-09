# ---------- CONFIG ----------
CC       = gcc
FLEX     = flex
BISON    = bison -d -v
SRC      = src
EXE      = draft

EXAMPLES := $(wildcard examples/*.dft)

# ---------- BUILD ----------
all: $(EXE)

$(EXE): $(SRC)/draft.l $(SRC)/draft.y \
        $(SRC)/ast.c $(SRC)/codegen.c $(SRC)/ast.h $(SRC)/main.c
	$(BISON) -o $(SRC)/draft.tab.c $(SRC)/draft.y
	$(FLEX)  -o $(SRC)/lex.yy.c     $(SRC)/draft.l
	$(CC) -o $@ $(SRC)/lex.yy.c $(SRC)/draft.tab.c \
              $(SRC)/ast.c $(SRC)/codegen.c $(SRC)/main.c -lfl

# run ARQ=examples/arquivo.dft
run: $(EXE)
	@ARQ ?= examples/hello.dft
	@echo ">> Rodando $(ARQ)"
	@./$(EXE) < $(ARQ)

test: $(EXE)
	@set -e
	@for f in $(EXAMPLES); do \
		echo "==> $$f";          \
		./$(EXE) < $$f;          \
	done
	@echo "Todos os testes passaram!"

clean:
	rm -f $(EXE) $(SRC)/lex.yy.c $(SRC)/draft.tab.* $(SRC)/draft.output \
	      temp.c temp.out

.PHONY: all run test clean
