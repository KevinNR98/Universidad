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
	CPD	#$9
	BLS	esNum
	BEQ	esLetra
	BPL	esLetra
esNum	INY		
esLetra INX	
	INX
	BNE	LOOP

FIN	BRA	FIN


	
Vector	FDB    'A,$5,'B,'b,'C,$1,'c,$14,$255,'Y,'F,00