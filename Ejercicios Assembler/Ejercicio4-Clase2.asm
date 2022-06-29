* Ejercicio simple de suma de dos valores de 32 bits
* Los dos valores se encuentran en memoria 

     ORG   $0000		
var1 RMB   4		
var2 RMB   4
res  RMB   5		
iter EQU   4  		; en C seria #define iter 4
	ORG	$c000
	LDAB	#iter
	CLR	res	*tambien limpia el carry

	LDX	#$0003	*Carga el indice de reg X, seria var1+3	
loop
	LDAA 	0,x	; var1+3
	ADCA	4,x	; var2+3
	STAA	9,x	; res+4
	DEX		; esto hace ix--, le resta 1 al indice
	DECB		; decrementa B
	BNE	loop	;va a saltar mientras no sea 0


* el finalmente si hay carry lo guardo en el byte mas signif.
	BCC 	FIN
	INC 	res

FIN	BRA 	FIN	*while(1)

*  esto no esta bien porque se trata de vector de constantes
* en RWM lo que CONCEPTUALMENTE esta mal
* pero el simulador lo admite, asi que aprovechamos para ganar tiempo
	ORG	$0000
	FDB	$FFFF,$FFFF,$0000,$0001
* si pongo codigo aca potencialmente generamos errores y asquerosos