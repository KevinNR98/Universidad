ROM		EQU	$C000
RAM		EQU	$0000
LEDS		EQU	$1004
TECLAS		EQU	$1003
RESET		EQU	$FFFE
IRQ		EQU	$FFF2
XIRQ		EQU	$FFF4
CONFIG		EQU	$1039
LCDDATA		EQU	$1040

MASKNMI		EQU	%10111111
MASKIRQ		EQU	%11101111
MASKEDGE	EQU	%00100000

		ORG	RAM
Coca		RMB	1
Manaos		RMB	1
Bichy		RMB	1
Goliat		RMB	1
		
		ORG	RAM
		Db	0,8,8,8

		ORG	RAM+20
SALDO		RMB	1

		

		ORG	ROM

		TPA
		ANDA	#(MASKNMI&MASKIRQ)
		TAP
		LDAA	CONFIG
		ORAA	#MASKEDGE 
		STAA	CONFIG
		
		CLR	LCDDATA
		CLR	SALDO
		JSR	MENUOPCIONES
FIN
		
		
		BRA	FIN


MENUOPCIONES
		LDX	#$0000
		CLR	LCDDATA
		LDY	#4
MENU
		LDAA	0,X
		ADDA	#'0
		STAA	LCDDATA
		INX
		DEY
		BEQ	Salir
		BRA	MENU
		
Salir	
		RTS
		



RUTINA_IRQ	
		LDAB	TECLAS
		ANDB	#%11110000
	
		CMPB	#128	
		BNE	salto1		;selecciono coca?

		LDAB	Coca		; hay stock?
		CMPB	#0
		BNE	conStock1
		LDAB	#'E
		STAB	LCDDATA
		BRA	salto4
conStock1
		LDAB	SALDO		;hay plata?
		CMPB	#150
		BLS	salto1
		
		LDAB	Coca		;descuento stock
		SBCB	#1
		STAB	Coca

		LDAB	SALDO		;descuento el saldo
		SBCB	#150
		STAB	SALDO

		
salto1
		
		CMPA	#64
		BNE	salto2		;selecciono coca?

		LDAB	Manaos		; hay stock?
		CMPB	#0
		BNE	conStock2
		LDAB	#'E
		BRA	salto4
conStock2
		LDAB	SALDO		;hay plata?
		CMPB	#120
		BLS	salto2
		
		LDAB	Manaos		;descuento stock
		SBCB	#1
		STAB	Manaos

		LDAB	SALDO		;descuento el saldo
		SBCB	#120
		STAB	SALDO
salto2
		CMPA	#32
		BNE	salto3		;selecciono coca?

		LDAB	Bichy		; hay stock?
		CMPB	#0
		BNE	conStock3
		LDAB	#'69
		BRA	salto4
conStock3
		LDAB	SALDO		;hay plata?
		CMPB	#90
		BLS	salto3
		
		LDAB	Bichy		;descuento stock
		SBCB	#1
		STAB	Bichy

		LDAB	SALDO		;descuento el saldo
		SBCB	#90
		STAB	SALDO
salto3
		CMPA	#16	
		BNE	salto4		;selecciono coca?

		LDAB	Goliat		; hay stock?
		CMPB	#0
		BNE	conStock4
		LDAB	#'E
		BRA	salto4
conStock4
		LDAB	SALDO		;hay plata?
		CMPB	#115
		BLS	salto4
		
		LDAB	Goliat		;descuento stock
		SBCB	#1
		STAB	Goliat

		LDAB	SALDO		;descuento el saldo
		SBCB	#115
		STAB	SALDO
		
salto4

		JSR	MENUOPCIONES

		RTI

RUTINA_XIRQ	
		LDAB	TECLAS
		ANDB	#%00001111
		CMPB	#2		;2pe
		BNE	paso2
		ADDA	#2
paso2

		CMPB	#5		;5pe
		
		BNE	paso5
		ADDA	#5
paso5
		CMPB	#10		;10pe
		BNE	paso10
		ADDA	#10
paso10
		LDAB	SALDO
		ABA
		STAA	SALDO
		
		RTI



		ORG	IRQ			
		DW	RUTINA_IRQ		
						
		ORG	XIRQ
		DW 	RUTINA_XIRQ