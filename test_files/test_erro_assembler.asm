section bizarre ; Erro Sessão Inválida
    SUB A ; Erro de Instrução na sessão errada (TEXT)
section text
    ADD A,B ; Erro de Número de argumentos inválido, esperado 1
    COPY A B ; Erro de Instrução mal formatada
    DIV 2; Erro de Instrução mal formatada
    INPUT C; Erro Rótulo não definido
    INPUT D+3; Erro Rótulo não definido
    COPY A ; Erro de Número de argumentos inválido, esperado 2
    const 24 ; Erro de Instrução na sessão errada (DATA)
section data
    const ; Erro de Número de argumentos inválido, esperado 1
A:  const 1
    space
B:  const 2
