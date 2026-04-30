; TITLE: lab_3_1cii
; Author: Goe Jie Ying& Teh Ru Qian
; Date: 26 June 2024

include Irvine32.inc

.data
	message1 BYTE "Calculate SUM (unsigned INT) index (Odd or Even) in array HELLO[6]", 0
	message2 BYTE "Integer Input: ", 0
	message3 BYTE "Result Sum HELLO[index]: ", 0dh, 0ah, 0dh, 0ah, 0
	message4 BYTE "Sum HELLO[even] index location: ", 0
	message5 BYTE "Sum HELLO[odd] index location: ", 0
	HELLO DWORD 6 DUP(?)
	TotalEVEN DWORD 0
	TotalODD DWORD 0

.code

main proc

	; Display initial message
	mov edx, OFFSET message1	; Calculate SUM(unsigned INT) index(Odd or Even) in array HELLO[6]
	call WriteString
	call Crlf
	call Crlf

	; Initialize loop for user input
	mov ecx, 6
	mov ebx, 0

	; User input loop
	inputLoop :
	mov edx, OFFSET message2	; Integer Input :
	call WriteString
	call ReadDec
	mov HELLO[ebx], eax
	add ebx, 4
	loop inputLoop

	call Crlf

	; Prepare for summation
	mov ebx, 0

	; Display intermediate message
	mov edx, OFFSET message3	; Result Sum HELLO[index]:
	call WriteString

	; Summation loop for even - indexed elements
	mov eax, HELLO[ebx]
	add TotalEVEN, eax
	add ebx, 8
	mov eax, HELLO[ebx]
	add TotalEVEN, eax
	add ebx, 8
	mov eax, HELLO[ebx]
	add TotalEVEN, eax

	; Reset ebx for odd - indexed elements summation
	mov ebx, 4

	; Summation loop for odd - indexed elements
	mov eax, HELLO[ebx]
	add TotalODD, eax
	add ebx, 8
	mov eax, HELLO[ebx]
	add TotalODD, eax
	add ebx, 8
	mov eax, HELLO[ebx]
	add TotalODD, eax

	; Display the sum of HELLO[even] index locations
	mov edx, OFFSET message4; Sum HELLO[even] index location :
	call WriteString
	mov eax, TotalEVEN
	call WriteDec
	call Crlf

	; Display the sum of HELLO[odd] index locations
	mov edx, OFFSET message5	; Sum HELLO[odd] index location :
	call WriteString
	mov eax, TotalODD
	call WriteDec
	call Crlf

	exit

main ENDP

END main
