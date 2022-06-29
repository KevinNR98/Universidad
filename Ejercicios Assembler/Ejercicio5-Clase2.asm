* Ejercicio simple de suma de dos valores de cualquier tamaño,(ITER BYTES)
* Los dos valores se encuentran en memoria 

iter EQU   6 		;Definimos el tamaño de palabra a sumar en bytes

     ORG   $0000		
var1 RMB   iter		
var2 RMB   iter
res  RMB   iter+1		
 		; en C seria #define iter 4
	ORG	$c000
	LDAB	#iter
	CLR	res	*tambien limpia el carry

	LDX	#iter-1	*Carga el indice de reg X	
loop
	LDAA 	0,x	
	ADCA	iter,x	
	STAA	(iter*2+1),x	
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
	FDB	$FFFF,$FFFF,$FFFF,$0000,$0000,$0001
* si pongo codigo aca potencialmente generamos errores y asquerosos