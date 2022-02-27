[bits 32]
[extern main]
call main
jmp $
%include "cpu/interrupt.asm"
