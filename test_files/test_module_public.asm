SECTION DATA
    theAnswer: const 42
    secretNumber: const 10
    public finalFrontier ; Public Before Declaration
    finalFrontier: SPACE
    hope: EXTERN ; E
BEGIN
    ADD hope; Using External Variables
    public hope ; Error Public Extern variable
    public theAnswer ; Public After Declaration
END
