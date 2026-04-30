; TITLE: Lab 3_1ci
; Author: Goe Jie Ying & Teh Ru Qian
; Date: 26 June 2024

include Irvine32.inc

.data
	message1 BYTE "Calculate Perimeter 2-Hexagon (LOOP and ADD instruction): ", 0dh, 0ah, 0
	message2 BYTE "Input Hexagon 1 (side length): ", 0
	message3 BYTE "Input Hexagon 2 (side length): ", 0
	message4 BYTE "Result of Perimeter Hexagon 1 and 2: ", 0dh, 0ah, 0
	message5 BYTE "Total Perimeter Hexagon 1 and 2: ", 0
	
	sideHex1 DWORD ?
	sideHex2 DWORD ?
	Perimeter_hexagon1 DWORD 0
	Perimeter_hexagon2 DWORD 0
	TotalPerimeter DWORD ?


.code

main proc

startProg :
	call Clrscr
	mov edx, OFFSET message1	; Calculate Perimeter 2 - Hexagon(LOOP and ADD instruction) :
	call WriteString
	call crlf

	mov edx, OFFSET message2	; Input Hexagon 1 (side length) :
	call WriteString
	call ReadDec
	mov sideHex1, eax

	mov edx, OFFSET message3	; Input Hexagon 2 (side length) :
	call WriteString
	call ReadDec
	mov sideHex2, eax

	call crlf
	call crlf

	mov ecx, 6

Addition :
	mov eax, sideHex1
	add Perimeter_hexagon1, eax
	mov eax, sideHex2
	add Perimeter_hexagon2, eax
	loop Addition


; Display individual perimeters
	mov edx, OFFSET message4	; Result of Perimeter Hexagon 1 and 2:
	call WriteString
	mov eax, Perimeter_hexagon1
	call WriteDec
	call crlf
	mov eax, Perimeter_hexagon2
	call WriteDec
	call crlf
	call crlf

; Calculate total perimeter
	mov eax, Perimeter_hexagon1
	add TotalPerimeter, eax
	mov eax, Perimeter_hexagon2
	add TotalPerimeter, eax

; Display total perimeter
	mov edx, OFFSET message5	; Total Perimeter Hexagon 1 and 2:
	call WriteString
	mov eax, TotalPerimeter
	call WriteDec
	call crlf

exit

main ENDP

END main
