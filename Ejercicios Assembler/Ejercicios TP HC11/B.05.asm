RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000
CANTVEC EQU	20

	;Vector RESET
	ORG	RESET
	DW	Main
		
	ORG	RAM
NRONEG	RMB	2
	;Comienzo del Codigo
	ORG	ROM
Main:	
	;Cargo el Stack Pointer
	LDS	#$00FF
	CLRA
	CLRB
	LDAB	#CANTVEC ;Le mando la cant del vec
	LDX	#vector	;dir de vec en X
	JSR	CANTNEGFIJA
FIN	BRA	FIN

	;Vector de nros signados
vector	DW  10,-20,-30,-30000,5000,31000,-32000,2,-31001,-32768,32767,23,-99,150,-15,9999,-3434,32,-12,20


;;;;Subrituna CANTNEGFIJA
;;;;;Recive la dir de vec en IX
;;;;;;Devuelve la cant de nros negativos
CANTNEGFIJA:
	;;Guardo los valosres de A por si lo modifico
	;;Para poder devolverlos
	PSHA
	;Voy a usar Y para leer el vector asi que lo guardo
	PSHY

	

loop	LDY	0,X
	BPL	noNeg
	INCA	;guardo la cant de nros negativos
noNeg	
	INX
	INX
	DECB	;;pasarselo por y que no me actualiza el flag de negative
	BNE	loop
	
	STAA	0,X	;VER DONDE GUARDAR EL VALOR DEL REG A
	PULY
	PULA
	RTS
	