RESET	EQU	$FFFE
RWM	EQU	$0000
ROM	EQU	$C000



	ORG	RESET
	ORG	RAM
	DW	MAIN


	ORG	ROM
MAIN	
	LDS	#$00FF
	CLRA
	CLRB
	LDX	#VECTOR
	LDY	#VECTOR2
	JSR	SUBRUTINA
FIN	BRA	FIN





;;;;;SUBRUTINA
;;;VECTOR CON 100 SIMBOLOS ASCII, LO RECORRO, SI ES UN NUMERO LO DIVIDO POR DOS
;;;SI ES UNA LETRA MAYUSCULA O MINUSCULA LE SUMO 128, SI ES OTRO CARACTER LO CAMBIO POR $20
SUBRUTINA:
	PSHA
	PSHB
	PSHY

	LDAA	0,X
	CMPA	#$'9
	