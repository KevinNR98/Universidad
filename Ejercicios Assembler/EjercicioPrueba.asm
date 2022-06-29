*Ejer Prueba
*IX recibe la dirección vector, termina en 0
*retorna en el registro IY la cantidad de elementos pares

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
	JSR	PAR

FIN	BRA	FIN
		;;vector de 16 bits
vector		DW	1000,2000,3999,4000,5555,6000,7777,8000,0


;;;;;SubRutina	PAR
;;;;;;Recibe la dir de un vec
;;;;;;;Devuelve la cant de nros pares en el registro Y
PAR
		PSHA
		PSHB
		CLRA
		CLRB

LOOP		LDD	0,X
		BEQ	FINRUTINA
		LSRD
		BCS	impar	; si no es cero es por que es impar, BCC si quiero contar impares
		INY		;cuenta par
impar
		INX
		INX
		BRA	LOOP

FINRUTINA	PULB
		PULA
		RTS