TITLE Lab2 Question 5
; Author: Teh Ru Qian & Goe Jie Ying
; Date: 2/6/2024


include Irvine32.inc
.data

.code
main proc

	mov dx, 0        ; Clear DX
	mov ax, 1000h    ; Load 1000h into AX
	mov cx, 25h      ; Load 25h into CX
	mul cx           ; Multiply AX by CX, storing the result in DX : AX

	call dumpregs

exit
main ENDP
END main