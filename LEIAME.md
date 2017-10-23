# Yet another Little asm

`yla` é uma liguagem assembly implementado do zero em C++ para um processador fictício abordado na disciplina de _Software Básico_. Atualmente conta apenas com o montador para criar o código de máquina e um pré-compilador no qual são avalidas algumas diretivas de preprocessamento e também macros.

A partir do conjunto de instruções implementados é permitido virtualmente escrever qualquer programa sendo portanto uma máquina de Turing completa [1]
(http://en.wikipedia.org/wiki/Turing_completeness)

## Grupo

 * João Pedro Carneiro Parada Franch - 120060795
 * Rafael Lima - 10013093

## Descrição das Pastas

 * src: arquivos fonte do programa
 * docs: documentação do programa (Gerada a partir do Doxygen)
 * test_files: Arquivos de teste usados

## Compilando
Para usar primeiro entre na pasta `src` e compile o programa através do comando

```
$ make
```

Caso deseje compilar a documentação, ainda na pasta `src` use o seguinte comando abaixo. Nota é necessário ter instalado Doxygen e Graphviz para poder gerar o gráficos de chamada.

```
$ make docs
```

Como forma de validar o funcionamento podem ser utilizados o teste automatizado a partir dos arquivos `.asm` dentro da pasta `test_files`. Novos arquivos podem ser incluidos na pasta. Serão executado para cada arquivo de entrada as 3 etapas (preprocessamento, expansão das macros e montagem) para tal basta executar o seguinte comando:

```
$ make clear-test; make test
```

## Guia de Uso

Uma vez compilado o programa `yla` permite a avaliação das diretivas preprocessamento, macros e verificação do uso da liguagem. Para tal é necessário especificar qual a operação desejada a partir dos parâmetros de entrada do programa. Pular uma destas etapas implicará em erro, uma vez que o programa assume que as etapas anteriores tenham sido executadas.

### Preprocessamento

Nesta fase são avaliadas somente as diretivas IF e EQU além da passagem de todas as letras para caixa alta. Comando:

```
yla arquivo_entrada.asm -p arquivo_entrada.pre
```

### Expansão das macros

São permitidos o uso de macros sem parâmetros. Estas começam sempre com MACRO e terminam com END. Para avaliar cada macro e substituir no código basta usar o seguinte comando:

```
yla arquivo_entrada.pre -p arquivo_entrada.mcr
```

### Montagem

No processo final de montagem é feito a analise de cada instrução e por fim é montado um arquivo objeto formado por números e espaços que poderá ser lido pelo simulador.
```
yla arquivo_entrada.mcr -p arquivo_entrada.pre
```
