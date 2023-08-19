MOV rax, 5
BRK

ADD rax, 5
BRK

MOV rax, 999999
BRK

CMP [rax], rax
JNE [rax]
BRK