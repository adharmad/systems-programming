;; Program which reads command line arguments from the stack

section .text
	global _start

msg		db	0xa		            ; message
len		equ	$ - msg
	
_start:	
	pop ebx			            ;  this is argc
	dec ebx

	pop ebp
	mov edx, 9			        ; message length (hardcoded)
	mov ecx, ebp		    	; message to write
	mov ebx, 1	    	    	; file descriptor(stdout)
	mov eax, 4			        ; system call no sys_write
	int 0x80	    		    ; call kernel

	call eol
	
	pop ebp
	mov edx, 3			        ; message length (hardcoded)
	mov ecx, ebp		    	; message to write
	mov ebx, 1	    	    	; file descriptor(stdout)
	mov eax, 4			        ; system call no sys_write
	int 0x80	    		    ; call kernel			

	call eol
	
	pop ebp
	mov edx, 2			        ; message length (hardcoded)
	mov ecx, ebp		    	; message to write
	mov ebx, 1	    	    	; file descriptor(stdout)
	mov eax, 4			        ; system call no sys_write
	int 0x80	    		    ; call kernel

	call eol
	
	mov eax, 1
	int 0x80

eol:	
	mov edx, len			    ; message length (hardcoded)
	mov ecx, msg		    	; message to write
	mov ebx, 1	    	    	; file descriptor(stdout)
	mov eax, 4			        ; system call no sys_write
	int 0x80	    		    ; call kernel
	ret		
