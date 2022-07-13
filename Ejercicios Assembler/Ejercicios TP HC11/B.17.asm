*b.17
*IX recibe la dirección vector, termina en 0
*retorna en el registro IY la cantidad de elementos impares


RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000

	ORG	RESET
	ORG	RAM
	DW	Main

	ORG	ROM	
Main
	LDS	#$00FF
	LDY	#0
	LDX	#Vector
	JSR	C24IMPBE

FIN	BRA	FIN

Vector	DB	$1,$2,$3,$4,$5,$6,$7,$8,$9,$a,$b,$c,0


;;;;;SubRutina	C24IMPBE
;;;;;;Recibe la dir de un vec
;;;;;;;Devuelve la cant de nros impares en el registro Y

C24IMPBE
		PSHA
		PSHB

		LDAA	0,X
LOOP		ASRA	
		BCC	noCarry
		INY
noCarry
		INX
		LDAA	0,X
		BEQ	FINRUTINA	
		BRA	LOOP

FINRUTINA	PULA
		RTS
