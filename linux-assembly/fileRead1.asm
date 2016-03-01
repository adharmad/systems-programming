; File read program in Linux assembly
;
; Assemble using	: $ nasm -f elf fileRead1.asm
; Link using    	: $ ld -s -o fileRead1 fileRead1.o

bits 32						            ; tell NASM to use 32 bits

global _start

section .bss
	buf:	resb	255	

	
section .data
	bufsize equ 11
				
section .text
	global _start				        ; declared for our linker ld
		
_start:				                    ; entry point
	pop ebx			                    ; argc
	pop ebx			                    ; argv[0]
	pop ebx			                    ; argv[1]

	mov eax, 5		                    ; sys_open
	mov ecx, 0		                    ; O_RDONLY
	int 0x80

	test eax, eax		                ; test valid file descriptor
	js exit			                    ; if signed, exit
	
	call file_function

exit:		
	mov ebx, eax		                ; save error no in ebx
	mov eax, 1		                    ; sys_exit
	int 0x80		                    ; bail out

file_function:
	mov ebx, eax		                ; file descriptor of file
	mov eax, 3		                    ; sys_read
	mov ecx, buf
	mov edx, bufsize

	int 0x80

	test eax, ex

	jnz print_file
	ret			                        ; return if error
	
print_file:
    ;; work in progress	
