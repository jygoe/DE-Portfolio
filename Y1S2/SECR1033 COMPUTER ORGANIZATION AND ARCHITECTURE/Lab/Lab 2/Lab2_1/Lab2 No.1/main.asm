TITLE lab2 Question 1
; Author: Teh Ru Qian & Goe Jie Ying
; Date: 2/6/2024


INCLUDE Irvine32.inc
.data
var1 word 1         ; declare var1 of word size(2byte) with 1d
var2 word 9         ; declare var2 of word size(2byte) with 9d

.code
main PROC
	mov ax, var1                    ; LINE1 
	mov bx, var2                    ; LINE2 
	xchg ax, bx                     ; LINE3 
	mov var1, ax                    ; LINE4
	mov var2, bx                    ; LINE5
	call DumpRegs
	exit
main ENDP
END main