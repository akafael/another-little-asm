; Show Fibonacci Sequence up to a given number

SECTION TEXT
        COPY    ZERO,   OLDER
        COPY    ONE,    OLD
        INPUT   LIMIT
FRONT:  LOAD    OLDER
        ADD     OLD
        STORE   NEW
        SUB     LIMIT
        JMPP    FINAL
        OUTPUT  NEW
        COPY    OLD,    OLDER
        JMP     FRONT
FINAL:  OUTPUT  LIMIT
        STOP
SECTION DATA
ZERO:   CONST   0
ONE:    CONST   1
OLDER:  SPACE
OLD:    SPACE
NEW:    SPACE
LIMIT:  SPACE
