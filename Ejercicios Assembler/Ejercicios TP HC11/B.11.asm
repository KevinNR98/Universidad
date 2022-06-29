RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000


	ORG	RESET
	ORG	RAM
	DW	Main


	ORG	ROM
MAIN:	
	LDS	#$00FF
	CLRA
	CLRB
	LDY	#0000
	LDX	#vector
	JSR	COMP2BEB
FIN	BRA	FIN

	;;Vector de 64 bits
vector	FDB  $FD,$30,$0A14,$02CF,$F5EC



;;Subrituna COMP2BEB
;;;Recive la dir del vec en IX
;;;;Retorna el valor complementado
COMP2BEB:
	PSHA
	PSHB
	PSHY
	
	LDY	0,X
	COM	1,Y
	
	
	RTS
				
	