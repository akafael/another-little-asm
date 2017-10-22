L1: EQU 1
L2: EQU 0
LOAD SPACE ;instrucao na secao errada

SECTION TEXT
IF L1
LOAD SPACE 
L3: EQU 2 ;diretiva na secao errada
IF L2
INPUT SPACE 
SECTION DATA
N: SPACE
