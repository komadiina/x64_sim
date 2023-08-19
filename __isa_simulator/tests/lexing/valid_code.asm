MOV RAX, RBX
__label:
MOV RCX, 40

ADD RCX, [40];
JMP __label;
NOT [rax]

CMP RAX, RBX
JGE __label

CMP RAX, RBX
