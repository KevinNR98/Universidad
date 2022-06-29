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
	JSR	ITOAU32BE
FIN	BRA	FIN
	
	;;Vector de numeros de 16 bits sin signo
Vector	DW  $1234,$5678


;;;;;SubRutina	ITOAU32BE
;;;;;;Recibe la dir de un vec
;;;;;;;que lo convierta a una cadena de caracteres ASCII, a partir de la dirección indicada por
;;;;;;;;el registro IY
ITOAU32BE:
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