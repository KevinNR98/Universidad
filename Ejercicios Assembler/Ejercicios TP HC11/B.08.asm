RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000

	;Vector RESET
	ORG	RESET
	DW	Main
		
	ORG	RAM
CANTVEC	RMB	1
	;Comienzo del Codigo
	ORG	ROM
Main:	
	;Cargo el Stack Pointer
	LDS	#$00FF
	CLRA
	CLRB
	CLR	CANTVEC
	LDX	#vector	;dir de vec en X
	JSR	PROMPOS

FIN	BRA	FIN

	;Vector de nros signados
vector	FDB  10,-20,-30,-128,255,100,-99,2,-60,-56,32,23,-90,15,-15,9,-34,32,-12,0


;;;;Subrituna PROMPOS
;;;;;Recive la dir de vec en IX
;;;;;;Devuelve la cant de nros negativos
PROMPOS:
	;;Guardo los valosres de A por si lo modifico
	;;Para poder devolverlos
	PSHA
	PSHY

loop	LDY	0,X
	BEQ	finVec
	BMI	Neg
	ADDD	0,X	; sumamos los valores positivos
Neg	INX
	INX
	LDY	CANTVEC
	INY		;cuenta la cant del vec	
	STY	CANTVEC	
	BNE	loop   	;termina si es el fin del vec
finVec	
	LDX	CANTVEC
	IDIV
	XGDX
	
	PULY
	RTS