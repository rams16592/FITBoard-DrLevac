;
; AssemblerApplication1.asm
;
; Created: 7/6/2016 1:52:00 PM
; Author : Chris
;

main:
	ldi r16, 0xFF
	ldi r17, 0x00
	OUT DDRB, r16
	ldi  r18, 6
    ldi  r19, 19
    ldi  r20, 174

	loop:
	OUT PINB, r16
	rjmp L1
	OUT PINB, r17
	rjmp loop

; A funtion to create a hard clock cycle delay
; grabbed from the internet at http://www.bretmulvey.com/avrdelay.html
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
    rjmp PC+1
