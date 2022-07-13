*B.06
*XI recibe la direccion de un vector, termina en 0.
*retorna la cantidad de numeros negativos.


RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000

	ORG	RESET
	ORG	RAM
	DW	MAIN
	
	ORG	ROM
MAIN		
	LDS	#$00FF
	LDX	#VECTOR
	LDAB	#0
	JSR	CANTNEGA
FIN	BRA	FIN

VECTOR DB	-1,-2,3,5,-18,4,0

CANTNEGA:
	
	LDAA	0,X
LOOP	BPL	NOESNEG
	INCB
NOESNEG
	INX
	LDAA	0,X
	BNE	LOOP
	RTS