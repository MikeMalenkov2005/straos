[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov bx, msg
call print

call load_kernel

call switch_to_pm

jmp $

BOOT_DRIVE: db 0

%include "boot/print.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/pm.asm"

msg: db "StraOS is booting...", 0

[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call read_disk
	ret

[bits 32]

BEGIN_PM:
	call KERNEL_OFFSET
	jmp $

times 510-($-$$) db 0              
dw 0xaa55
