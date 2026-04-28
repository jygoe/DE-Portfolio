TITLE lab2_4
; Author: GJY& TRQ
; Date: 4 June 2024

include irvine32.inc
.data
	var1 WORD 40	; 0028h
	var2 WORD 10	; 000Ah
	var4 WORD ?

.code
main proc
	mov ax, var1	; LINE1
	mov bx, 5		; LINE2
	mul bx			; LINE3
	mov bx, var2	; LINE4
	sub bx, 3		; LINE5
	div bx			; LINE6
	mov var4, ax	; LINE7
exit
main endp
end main
