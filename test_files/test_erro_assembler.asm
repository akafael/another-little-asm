section bizarre ; Erro Sessão Inválida
    SUB A ; Erro de Instrução na sessão errada (TEXT)
section data
        const ; Erro de Número de argumentos inválido, esperado 1
    A:  const 1
        space
    B:  const 2
    ZERO: const 0
section text
    ADD A,B ; Erro de Número de argumentos inválido, esperado 1
    COPY A B ; Erro de Instrução mal formatada
    COPY 1,B ; Erro de Tipo de Argumento Errado
    COPY A,2 ; Erro de Tipo de Argumento Errado
    COPY A,B ; Erro de Uso de Constante como Argumento
    COPY A+1,B+1 ; Erro de Uso de Constante como Argumento
    INPUT A ; Erro de Uso de Constante como Argumento
    LOAD B ; Erro de Uso de Constante como Argumento
    DIV 2; Erro de Instrução mal formatada
    DIV ZERO ; Erro de Divisão por zero
    INPUT C; Erro Rótulo não definido
    INPUT D+3; Erro Rótulo não definido
    COPY A ; Erro de Número de argumentos inválido, esperado 2
    const 24 ; Erro de Instrução na sessão errada (DATA)
