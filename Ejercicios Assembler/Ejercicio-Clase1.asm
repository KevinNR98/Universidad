* Ejercicio simple de suma de dos valores de 8 bits
* Los dos valores se encuentran en memoria 

	ORG	$0000
* todo lo que vaya aca va a estar a partir de la dir 0000
res  RMB   2 		*Ocupara la direccion 0000 H y 0001 L
var1 RMB   1		*0002
var2 RMB   1		*0003

	ORG	$c000
	CLR	res
	LDAA	var1
	ADDA	var2
	BCC	noCarry
	INC 	res
noCarry
	STAA	res+1
FIN	BRA 	FIN
