TITLE lab2_2
; Author: Goe Jie Ying & Teh Ru Qian
; Date: 4 June 2024

include irvine32.inc

.data
	Rval DWORD ?	; declare a variable Rval with the uninitialized value of Double Word size
	Xval DWORD 26	; declare a variable Xval with the value 26d(0000001Ah) of Double Word size
	Yval DWORD 30	; declare a variable Yval with the value 30d(0000001Eh) of Double Word size
	Zval DWORD 40	; declare a variable Zval with the value 40d(00000028h) of Double Word size

.code
	main proc
	mov eax, Xval	; LINE1
	neg eax			; LINE2
	mov ebx, Yval	; LINE3
	sub ebx, Zval	; LINE4
	add eax, ebx	; LINE5
	inc eax			; LINE6
	mov Rval, eax	; LINE7

exit
main endp
end main