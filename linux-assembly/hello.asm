; Hello world program in Linux assembly
; Beginning Linux assembly studies
;
; Assemble using	: $ nasm -f elf hello.asm
; Link using    	: $ ld -s -o hello hello.o
	
section .text
global _start		                ; must be declared for our linked ld

msg		db	'Hello World!', 0xa	    ; message
len		equ $ - msg
	
_start:					       	    ; entry point
		
	mov	edx, len			        ; message length
	mov	ecx, msg		    	    ; message to write
	mov	ebx, 1		    	    	; file descriptor(stdout)
	mov	eax, 4				        ; system call no sys_write

	int	0x80		    		    ; call kernel

	mov	eax, 1		    		    ; system call no sys_exit
	int	0x80		        	    ; call kernel

