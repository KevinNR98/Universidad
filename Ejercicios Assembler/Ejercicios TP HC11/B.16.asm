RESET	EQU	$FFFE
RAM	EQU	$0000
ROM	EQU	$C000


	;Vectore de Reset
	ORG	RESET
	ORG	RAM
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
	JSR	ALIGN4
FIN	BRA	FIN
	
	;;Vector de numeros de 16 bits sin signo
	ORG	$0000
Vector	DW  $0000,$0001,$0002,$0003,$0004,$0005,$0006,$0007$0008,$0009,0


;;;;;SubRutina	ALIGN4
;;;;;;Recibe la dir de un vec
;;;;;;;
;;;;;;;;el registro IY
ALIGN4
	;;Guardo A y B por que los voy a usar
	PSHA
	PSHB
	PSHY
	
	LDD	0,X
LOOP:	
	INX
	INX
	LDD	0,X
	BEQ	FINRUTINA
	TBA
	ANDA	#%00000011 ;podría usar tambien #$01 o #01	
	BNE	noAli
	BRA	LOOP
noAli
 	INY
	BRA	LOOP

FINRUTINA:
	;;Ahora D tiene la Dir del minimo
	PULY
	PULB
	PULA
	RTS