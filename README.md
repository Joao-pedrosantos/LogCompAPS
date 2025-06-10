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

A gramática completa da Draft pode ser encontrada no arquivo `docs/gramatica_draft.txt`.

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
penso limite é 0
questiono "Somar de 1 até quanto?" e guardo em limite

penso soma é 0
penso i é 1

continuo enquanto i <= limite
    penso soma é soma + i
    penso i é i + 1
fim

digo "A soma de 1 até " + limite + " é " + soma
```

---

## 🔥 Curiosidades

- Draft é inspirado em técnicas literárias de **fluxo de consciência**, como usado no livro **Angústia**, de **Graciliano Ramos**.
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
    Se quiser usar os exemplos já prontos, execute:
    ```bash
    make examples
    ```
    ou

   ```bash
    make test
    ```

## 📚 Créditos

Este projeto foi desenvolvido por **João Pedro Rodrigues dos Santos** como parte da disciplina **Lógica da Computação – Insper – 2025/1**.
