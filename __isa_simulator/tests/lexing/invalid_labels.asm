ADD rax, [5]
_labelOK:
    CMP 5, 5
    JNE _labelOK

1:
    NOT rax

_i_am_wrong!!!:
    ADD 5, 5