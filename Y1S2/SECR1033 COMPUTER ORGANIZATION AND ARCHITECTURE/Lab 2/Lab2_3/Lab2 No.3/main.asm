TITLE Lab2 Question3
; Author: Teh Ru Qian& Goe Jie Ying
; Date: 2 / 6 / 2024
; Purpose: Arithmetic expression : var4 = [(var1 * var2) + var3] - 1

include irvine32.inc

.data
var1 DWORD 5      ; declare a varible val1 of doubleword size(initialized with 5d)
var2 DWORD 10     ; declare a varible val2 of doubleword size(initialized with 10d)
var3 DWORD 20     ; declare a varible val3 of doubleword size(initialized with 20d)
var4 DWORD ?      ; declare a varible val4 of doubleword size(uninitialized)

.code
	main proc
	mov eax, var1           ; LINE1
	mul var2                ; LINE2
	add eax, var3           ; LINE3
	dec eax                 
	mov var4, eax           ; LINE4

	call dumpregs

exit
main endp
end main
