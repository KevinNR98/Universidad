ROM		EQU	$C000	*ESTE EJERCICIO ES COMO HACER UN FOR QUE RECORRE EL VECTOR
RAM		EQU	$0000	*FOR(B=32;B>0;B--)
			*{A=VECTOR(X))
TAM		EQU	32

		ORG 	RAM	DEFINO VALORES DE LAS VARIABLES
VECTOR		RMB	TAM	ARRANCA EN LA POS 0 DE MEMORIA	
NUMROS		RMB	TAM	ARRANCA EN LA POS 32 DE MEMORIA	
MAYUS		RMB	TAM
MINUS		RMB	TAM
PUNTNUM	RMB	2                                                                                                                                                    
PUNTMAY	RMB	2
PUNTMIN	RMB	2

INICIO 
	LDX	#VECTOR	PUNTERO, CARGO EL REGISTRO INDICE X CON LA POSICION DEL VECTOR 
	LDY	#NUMROS 
	STY	PUNTNUM
	LDY	#MAYUS 
	STY	PUNTMAY
	LDY	#MINUS
	STY	PUNTMIN

	LDAB	#TAM	LE DOY EL TAMA�O DEL VECTOR AL ACUM B PARA PODERE RECORRERLO	
LOOP
	LDAA 	0,X	CARGO EL ACUMULADOR A CON LA PRIMERA POSICION DEL VECTOR Y SIEMPRE APUNTA A X YA QUE LO VOY INCREMENTANDO

			*para que solo me copie los numeros seria este if((a>='a')&&(a<='z'))

	CMPA	#'z	COMPARE EL ACUMULADOR A CON z EN ASCII
	BHI	SIGUE	SI ES MAYOR QUE z NO VA A ESTAR COMOPRENDIDO ENTRE a Y z, SALTA SI ES MAYOR
	CMPA	#'a	COMPARE EL ACUMULADOR A CON 0 EN ASCII
	BHS	ESMINUS	SALTA SI ES MAYOR O IGUAL QUE 0

			*para que solo me copie los numeros seria este if((a>='A')&&(a<='Z'))

	CMPA	#'Z	COMPARE EL ACUMULADOR A CON Z EN ASCII
	BHI	SIGUE	SI ES MAYOR QUE Z NO VA A ESTAR COMOPRENDIDO ENTRE A Y Z, SALTA SI ES MAYOR
	CMPA	#'A	COMPARE EL ACUMULADOR A CON 0 EN ASCII
	BHS	ESMAYUS	SALTA SI ES MAYOR O IGUAL QUE 0

			*para que solo me copie los numeros seria este if((a>='0')&&(a<='9'))

	CMPA	#'9	COMPARE EL ACUMULADOR A CON 9 EN ASCII
	BHI	SIGUE	SI ES MAYOR QUE 9 NO VA A ESTAR COMOPRENDIDO ENTRE 0 Y 9, SALTA SI ES MAYOR
	CMPA	#'0	COMPARE EL ACUMULADOR A CON 0 EN ASCII
	BHS	ESNUMERO	SALTA SI ES MAYOR O IGUAL QUE 0

	*LDAA	#$ff	esto es para reiniciar el 2do vector en ff otra vez
SIGUE	
	INX		INCREMENTO EL REGISTRO X
	DECB		DECREMENTO B PORQUE TERMINA CUANDO EL VECTOR ES RECORRIDO COMPLETAMENTE
	BNE	LOOP	SI B NO ES IGUALA A 0 LOOPEA, CUANDO DECREMENTO MIRA SI EL FLAG ZERO ES 1, SI ES UNO QUIERE DECIR QUE B ERA 1 Y LE RESTE 1 Y DIO 0


FIN	BRA	FIN

ESMINUS
	LDY 	PUNTMIN
 	STAA	0,Y
	INY
	STY 	PUNTMIN	
	BRA	SIGUE
ESMAYUS
	LDY 	PUNTMAY
 	STAA	0,Y
	INY
	STY 	PUNTMAY	
	BRA	SIGUE	

ESNUMERO
	LDY 	PUNTNUM
 	STAA	0,Y
	INY
	STY 	PUNTNUM
	BRA	SIGUE

	ORG	VECTOR

	DB	$32,$39,'R,'i,'b,'e,'r,'s
	DB	'o,'s','d','e,'l,'a,'B,$41
	DB	097,103,114,097,110,100,101,100
	DB	101,109,117,122,122,097,'5,'0

		