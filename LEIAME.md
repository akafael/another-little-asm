# Yet another Little asm

`yla` é uma liguagem assembly implementado do zero em C++ para um processador fictício abordado na disciplina de _Software Básico_. Atualmente conta o montador para criar o código de máquina e um pré-compilador no qual são avalidas algumas diretivas de preprocessamento e também macros.

A partir do conjunto de instruções implementados é permitido virtualmente escrever qualquer programa sendo portanto uma máquina de Turing completa [1](http://en.wikipedia.org/wiki/Turing_completeness)

`yld` é um ligador implentado para combinar múltiplos arquivos objetos gerados a partir do montador `yla`.

`ylo` é um carregador implementado para simular a o processo de carregamento na memória e execução do programa a partir do processador fictício.

## Grupo

 * João Pedro Carneiro Parada Franch
 * Rafael Lima
 * Túlio Mariano da Silva Lima

## Descrição das Pastas

 * src: arquivos fonte do programa
 * docs: documentação do programa (Gerada a partir do Doxygen)
 * test_files: Arquivos de teste usados

## Compilando
Para compilar, primeiro entre na pasta `src` e compile o programa através do comando

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
A saída dos programas de testes pode ficar muito grande e dispendiosa para comparar se houve alterações entre um teste o outro. Tal pode ser resolvido usando o programa `diff` para comparar e redirencionando a saída dos erros para um arquivo separado a partir do seguintes comando:

```
make clear-all
make test 2> ../test_files/erros.txt
diff ../test_files/expected/errors.txt ../test_files/erros.txt
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

### Ligador

O ligador funciona como um programa a parte o qual recebe como parâmetro de entrada os nomes dos arquivos objetos e gera um arquivo de saída sem extensão com o nome do primeiro arquivo objeto fornecido. É suportado qualquer número de arquivos de entrada.

```
yld arquivo_principal.o modulo1.o modulo2.o
```

### Carregador

O carregador divide o programa fornecido em pedaços (chucks) de memória representados por arquivos de saída no formato `.im`, caso não ocorra nenhum problema o programa é simulado.

```
ylo programa [NUM_CHUCKS] [SIZE_CHUNK_1] [SIZE_CHUNK_2] ... [SIZE_CHUNK_N] [ADDR0_CHUNK_1] [ADDR0_CHUNK_2] ... [ADDR0_CHUNK_N]
```

Exemplo para um programa dividido em 3 chucks de memória com tamanhos 10, 20 e 30 e endereços iniciais 1000, 2000 e 3000 respectivamente:

```
ylo programa 3 10 20 30 1000 2000 3000
```
