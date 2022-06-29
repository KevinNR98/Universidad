RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000

	;Vector de Reset
	ORG	RESET
	ORG	RAM
	DW	MAIN
	
	;;;Inicio de programa
	ORG 	ROM


MAIN
	CLRA
	CLRB
	LDX	#vector
	LDY	#0
LOOP	LDD	0,X
	BEQ	FIN
	CPD	#'a
	BMI	esMayus
	BEQ	esMinus
	BPL	esMinus
esMayus	INY		;cuento la cant de mayusculas
esMinus	INX	
	INX
	BNE	LOOP

FIN	BRA	FIN


	
Vector	FDB    'A,'a,'B,'b,'C,'C,'c,00
	