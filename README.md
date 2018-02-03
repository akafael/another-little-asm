# Yet another Little ASM

`yla` is an custom Assembly-like language, implemented from scratch in C++. Name inspired on [my-little-asm](https://github.com/alexdantas/my-little-asm) deverloped by @alexdantas witch was also deverloped as _System Software_ class assigment at UnB. So far, it has an `assembler` (to create machine code), a `linker`, a `loader` and a `simulator`.

This is an example on how Assembly languages work - a set of human-readable instructions that are translated into machine code. Normally the language would be designed for some hardware to execute, but in our case we simulate it step by step.

With our basic instruction set we can potentially write any existing program out there - also called [Turing-completeness](http://en.wikipedia.org/wiki/Turing_completeness).

We have a parser that reads each instruction on the text file and converts them into integers - indexing all 14 possible instructions.

First, make sure to compile everything by doing:

```
$ make
```

## Sample code

```asm
SECTION TEXT
ROT: INPUT N1
    COPY N1, N4 ; Comentary
    COPY N2, N3
    COPY N3, N3 + 1
    OUTPUT N3 + 1
    STOP

SECTION DATA
N1: SPACE
N3: SPACE  4        ; Array of size 4
N2: CONST  -0x10    ; Look ma, hex constant!
```

## Language definition

`yla` follows a MIPS Assembly-like syntax.

Highlights:

* 14 instructions.
* `;` starts comment until the end of line.
* Labels references memory addresses.
* Accumulator register (`ACC`) implied on arithmetic instructions.
* Files with `.asm` extension.

Code is divided in two sections:

* Text section (for actual code)
* Data section (for variables and constants)

## Instructions

| Name                | Instruction  | Description                |
| :-----------------: | :----------: | :------------------------: |
| Add                 | `ADD`        | `ACC <- ACC + MEM[OP]`     |
| Subtract            | `SUB`        | `ACC <- ACC - MEM[OP]`     |
| Multiply            | `MULT`       | `ACC <- ACC * MEM[OP]` |
| Divide              | `DIV`        | `ACC <- ACC / MEM[OP]` |
| Jump Unconditional  | `JMP`        | `PC  <- OP` |
| Jump if Negative    | `JMPN`       | `If ACC < 0 then PC <- OP` |
| Jump if Positive    | `JMPP`       | `If ACC > 0 then PC <- OP` |
| Jump if Zero        | `JMPZ`       | `If ACC = 0 then PC <- OP` |
| Copy                | `COPY`       | `MEM[OP2] <- MEM[OP1]` |
| Load from Memory    | `LOAD`       | `ACC <- MEM[OP]` |
| Store into Memory   | `STORE`      | `MEM[OP] <- ACC` |
| Store Input         | `INPUT`      | `MEM[OP] <- STDIN` |
| Output Memory       | `OUTPUT`     | `STDOUT <- MEM[OP]` |
| Stop Execution      | `STOP`       | `stops program` |

Note:

* `MEM[OP]` means memory address specified by operand and `PC`
  is the program counter (current instruction address).

## Directives

| Name            | Effect  |
| :-------------: | :-----: |
| `SECTION TEXT`  | Signals begin of instructions. |
| `SECTION DATA`  | Start of data definitions. |
| `SPACE`         | Saves an empty space on memory for data storage.|
| `SPACE N`       | Saves an empty array in memory of size `N`. |
| `CONST X`       | Saves a constant of value `X` in memory. |
| `CONST X`       | Saves a constant of value `X` in memory. |
