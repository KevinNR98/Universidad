* Ejercicio simple de suma de dos valores de 32 bits
* Los dos valores se encuentran en memoria 

     ORG   $0000		
var1 RMB   4		
var2 RMB   4
res  RMB   5		

	ORG	$c000
	CLR	res	*tambien limpia el carry
* sumo el primer byte menos significativo
	LDAA 	var1+3
	ADDA	var2+3
	STAA	res+4
* el siguiente, arrastrando carry
	LDAA 	var1+2
	ADCA	var2+2
	STAA	res+3
* el siguiente, arrastrando carry
	LDAA 	var1+1
	ADCA	var2+1
	STAA	res+2
* el siguiente, arrastrando carry
	LDAA 	var1
	ADCA	var2
	STAA	res+1
* el finalmente si hay carry lo guardo en el byte mas signif.
	BCC 	FIN
	INC 	res

FIN	BRA 	FIN	*while(1)

*  esto no esta bien porque se trata de vector de constantes
* en RWM lo que CONCEPTUALMENTE esta mal
* pero el simulador lo admite, asi que aprovechamos para ganar tiempo
	ORG	$0000
	DB	$FF,$FF,$FF,$FF,$00,$00,$00,$01
* si pongo codigo aca potencialmente generamos errores y asquerosos