;;; Valores Cosntantes
LEDS		EQU $1004
TECLAS 		EQU $1003
valor1		EQU 1
valor2		EQU 33
valor3		EQU 65
led1		EQU 1
led2		EQU 3
led3		EQU 7


ROM		EQU $C000
RAM		EQU $0000
RESET		EQU $FFFE

		ORG ROM
Init:		
		;;Inicializacion de variables o elementos
		;; Ponemos los LEDS en estado apagado
		CLR LEDS
		CLR TECLAS

		
Main:
		;; Loop infinito donde leemos las teclas
		;; y las copiamos a los LEDS 
		LDAA TECLAS
		LDAB #led1
		CMPA #valor1
		BMI  noPrendo
		STAB LEDS
noPrendo
		LDAB #valor2
		LDAB #led2
		CMPA #valor2
		BMI  noPrendo2
		STAB  LEDS
noPrendo2
		LDAB #valor3
		LDAB #led3
		CMPA #valor3
		BMI  noPrendo3
		STAB  LEDS	
noPrendo3
		CLR TECLAS
		BRA MAIN



		ORG RESET
		DW  Init