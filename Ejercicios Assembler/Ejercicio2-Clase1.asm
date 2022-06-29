* Ejercicio simple de suma de dos valores de 16 bits
* Los dos valores se encuentran en memoria 

	ORG	$0000
* todo lo que vaya aca va a estar a partir de la dir 0000
res  RMB   3 		*0000,0001,0002
var1 RMB   2		*0003,0004
var2 RMB   2		*0005,0006

	ORG	$c000
	CLR	res	*solo limpia 0000(primer byte)

	LDD	var1
	ADDD	var2
	BCC	noCarry
	INC 	res
noCarry
	STD	res+1
FIN	BRA 	FIN	*while(1)
*  esto no esta bien porque se trata de vector de constantes
* en RWM lo que CONCEPTUALMENTE esta mal
* pero el simulador lo admite, asi que aprovechamos para ganar tiempo
	ORG	$0003
	FDB	$FFFF,$0001