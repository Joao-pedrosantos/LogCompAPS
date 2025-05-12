# Draft

Uma linguagem de programação inspirada no fluxo de consciência, criada como parte da APS de Lógica da Computação – 2025/1.

Draft simula o processo natural de pensamento humano, onde ideias surgem de forma livre e são transformadas em ações. Cada programa em Draft é como um rascunho de pensamentos: fluído, expressivo e natural.

---

## ✨ Motivação

O objetivo do Draft é romper com a rigidez tradicional da programação e abraçar o estilo de escrita humana.  
Em vez de comandos secos como `if`, `while`, `print`, a linguagem utiliza termos como `penso`, `considero`, `questiono`, `digo`, narrando o processo de pensamento.

---

## 📜 Características

- **Sintaxe baseada em linguagem natural** (português).
- **Fluxo narrativo**: comandos soam como pensamentos vivos.
- **Condicionais** como ponderações (`considero`, `talvez`).
- **Loops** como persistência de ideias (`continuo enquanto`).
- **Entrada e saída** representadas como diálogo (`questiono`, `digo`).
- **Atribuições** como concepções (`penso x é valor`).

---

## 🔣 Gramática (EBNF)

A gramática completa da Draft pode ser encontrada no arquivo `gramatica_draft.txt`.

Principais construções:

| Construção | Exemplo |
|------------|---------|
| Atribuição | `penso idade é 18` |
| Input      | `questiono "Qual sua idade?" e guardo em idade` |
| Output     | `digo idade` |
| Condicional| `considero idade > 18 então ... talvez ... fim` |
| Laço       | `continuo enquanto idade < 100 ... fim` |

---

## 🧪 Exemplo de Código (.dft)

```plaintext
penso idade é 0
questiono "Qual sua idade?" e guardo em idade

considero idade maior que 18 então
    digo "Você é maior de idade"
talvez
    digo "Você ainda é menor"
fim

penso contador é 0
continuo enquanto contador menor que 3
    digo "Contando: " + contador
    penso contador é contador + 1
fim
```

---

## 🔥 Curiosidades

- Draft é inspirado em técnicas literárias de **stream of consciousness**.
- Reflete o desejo de criar programas mais **humanos, expressivos e intuitivos**.
- Utiliza a extensão `.dft` para seus arquivos.

---

## 🚀 Como Executar

1. Rode o arquivo makefile para compilar o interpretador:
   ```bash
   make
   ```

2. Execute o interpretador com um arquivo Draft:
   ```bash
   ./draft < <seu_arquivo.dft>
   ```



## 📚 Créditos

Este projeto foi desenvolvido por **João Pedro Rodrigues dos Santos** como parte da disciplina **Lógica da Computação – Insper – 2025/1**.
