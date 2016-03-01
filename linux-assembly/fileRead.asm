; File read program in Linux assembly
;
; Assemble using	: $ nasm -f elf fileRead.asm
; Link using    	: $ ld -s -o fileRead fileRead.o

bits 32						; tell NASM to use 32 bits

global _start
	
section .data

filename	db    'test.txt', 0xa		; name of the file
size		equ   10			        ; hardcoding size to 10
msg1		db    'open failed', 0xa
msg1_size	equ   $-msg1
buffer		times 4 DB 0
	
section .text
	global _start				        ; declared for our linker ld
		
_start:						            ; entry point

	;; Open the file
	pop ebx
	pop ebx					            ;  get filename from stack
	pop ebx

	;;  print the file name
	
	mov ecx, 0				            ; O_RDONLY
	;mov ebx, filename			        ; file name
	mov eax, 5				            ; system call number (sys_open)
	int 0x80				            ; call kernel
	
	test eax, eax				        ; test what we got

	jnz file_function			        ; else call the file read function
	jmp finish
	
error:		
	mov ecx, msg1
	mov edx, msg1_size
	call print_function

	;js	finish				            ; if sign, go to exit

finish:
	;;  Print out something and exit
	mov	edx, msg1_size			        ; message length
	mov	ecx, msg1		    	        ; message to write
	mov	ebx, 1		    	    	    ; file descriptor(stdout)
	mov	eax, 4				            ; system call no sys_write
	int	0x80		    		        ; call kernel
	
	mov	eax, 1				            ; system call number (sys_exit)
	int	0x80				            ; call kernel

read_function:
	;; Now read from the file. file descriptor is in eax
	mov edx, size				        ; address if size in edx
	mov ecx, buffer				        ; address of buffer in ecx
	mov ebx, 0				            ; stdin
	mov eax, 3				            ; sys_read
	int 0x80				            ; call kernel
	
	test eax, eax				        ; test what we got
	js finish 
	jz finish

	;; Now that we have read the bytes, let us write them!
	mov	edx, eax			            ; no of bytes read
	mov	ebx, 1				            ; file descriptor(stdout)
	mov	eax, 4				            ; system call no sys_write
	int	0x80				            ; call kernel

	ret

file_function:
	;; Now read from the file. file descriptor is in eax
	mov edx, size				        ; address if size in edx
	mov ecx, buffer				        ; address of buffer in ecx
	mov ebx, eax				        ; file descriptor to read from
	mov eax, 3				            ; sys_read
	int 0x80				            ; call kernel
	
	test eax, eax				        ; test what we got
	js finish 
	jz finish

	;; Now that we have read the bytes, let us write them!
	mov	edx, eax			            ; no of bytes read
	mov	ebx, 1				            ; file descriptor(stdout)
	mov	eax, 4				            ; system call no sys_write
	int	0x80				            ; call kernel

	ret

print_function
	;; ecx and edx already set up before calling this
	mov	ebx, 1				            ; file descriptor(stdout)
	mov	eax, 4				            ; system call no sys_write
	int	0x80				            ; call kernel
	ret
