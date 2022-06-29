RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000


	;Vectore de Reset
	ORG	RESET
	ORG	RAM
dirmin	RMB	2
	DW	Main
	
	
	;Comienzo de Codigo
	ORG	ROM
Main
	;Cargamos el stack pointer
	LDS	#$00FF
	CLRA
	CLRB
	LDY	#0000
	LDX	#Vector
	JSR	POSMIN
FIN	BRA	FIN
	
	;;Vector de numeros signados de (16 bits)
	;;Termina con 0
Vector	DW  10,-20,-30,-128,255,100,-99,2,-60,-56,32,23,-30000,15,-15,9,-32000,32,-12,0


;;;;;SubRutina	POSMIM
;;;;;;Recibe la dir de un vec
;;;;;;;Devuelve la pos de un el nro min del vec
POSMIN:
	;;Guardo A y B por que los voy a usar
	PSHA
	PSHB
	PSHY

	LDD	0,X
	STX	dirmin
	
LOOP:
	INX
	INX
	LDY	0,X
	BEQ	FINRUTINA
	;;Si sigue, el elemento no es 0
	CPD	0,X
	;;Si D es menor que 0,X seguimos
	BLE	LOOP
	;;Si es menor, cambiamos
	LDD	0,X
	STX	dirmin
	BRA	LOOP

FINRUTINA:
	;;Ahora D tiene la Dir del minimo
	LDX	dirmin   ;GURADO EL MENOR EN IX
	PULY
	PULB
	PULA
	RTS