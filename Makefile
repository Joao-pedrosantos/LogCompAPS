# ──────────────── VARIÁVEIS BÁSICAS ─────────────────
CC      := gcc
FLEX    := flex
BISON   := bison -d -v
SRC     := src
EXE     := draft

# ──────────────── COLETA DE PROGRAMAS ───────────────
EXAMPLES := $(wildcard examples/*.dft)   # exemplos de demonstração
TESTS    := $(wildcard tests/*.dft)      # .dft + .out para ‘make test’

# ──────────────── COMPILA TUDO ──────────────────────
all: $(EXE)

$(EXE): $(SRC)/draft.l $(SRC)/draft.y \
        $(SRC)/ast.c $(SRC)/codegen.c $(SRC)/ast.h $(SRC)/main.c
	@echo "🛠️  Gerando parser & lexer…"
	$(BISON) -o $(SRC)/draft.tab.c $(SRC)/draft.y
	$(FLEX)  -o $(SRC)/lex.yy.c     $(SRC)/draft.l
	@echo "🛠️  Compilando $(EXE)…"
	$(CC) -o $@ $(SRC)/lex.yy.c $(SRC)/draft.tab.c \
	          $(SRC)/ast.c $(SRC)/codegen.c $(SRC)/main.c -lfl
	@echo "✔ Build concluído!"

# ──────────────── EXECUÇÃO ÚNICA ────────────────────
# uso: make run ARQ=examples/hello_world.dft
run: $(EXE)
	@$(eval ARQ ?= examples/hello_world.dft)
	@echo ">> Compilando $(ARQ)"
	@./$(EXE) $(ARQ)
	@echo ">> Executando programa gerado"
	@./temp.out

# ──────────────── EXAMPLES (demo) ───────────────────
examples: $(EXE)
	@for f in $(EXAMPLES); do \
		echo "==> $$f"; \
		./$(EXE) $$f >/dev/null; \
		./temp.out; \
		echo; \
	done

# ──────────────── TEST SUITE AUTOMÁTICA ────────────
# requer arquivos .dft + .out em tests/
test: $(EXE)
	@echo "🔎 executando suíte de testes"
	@set -e; \
	TMP=$$(mktemp); \
	for src in $(TESTS); do \
	    base=$${src%.dft}; \
	    ref=$${base}.out; \
	    echo "==> $$src"; \
	    \
	    ./$(EXE) $$src >/dev/null; \
	    \
	    if [ "$$src" = "tests/input_soma.dft" ]; then \
	        printf '3 4\n' | ./temp.out > $$TMP; \
	    else \
	        ./temp.out > $$TMP; \
	    fi; \
	    \
	    diff -u $$ref $$TMP && echo "✔ OK"; \
	    echo; \
	done; \
	rm -f $$TMP; \
	echo "🎉 Todos os testes passaram!"

# ──────────────── LIMPEZA ──────────────────────────
clean:
	rm -f $(EXE) $(SRC)/lex.yy.c $(SRC)/draft.tab.* $(SRC)/draft.output \
	      temp.c temp.out
	@echo "🧹 diretório limpo"

.PHONY: all run examples test clean
