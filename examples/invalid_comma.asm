__LABEL:
    MOV RAX, RCX
    MOV r1, [123];
    MOV [rax], 500;
    DIV [rax], [rdx];
    BREAKPOINT
    MUL 5, 15 

__loop:
    ADD 1, 2,
