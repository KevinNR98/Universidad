*recorro un vector de elementos de 8 bits 
*
*
RWM	EQU	0
ROM	EQU	$C000
valores EQU	19
	
	ORG	RWM
ceros	RMB	1
vec	RMB	valores
dummy 	RMB	1	;esta variable no la uso, pero quiero su direccion
	
	ORG	ROM

	CLR 	ceros	
	LDX	#vec
bucle	LDAA 	0,x
	BNE	noCero
	INC	ceros
noCero	INX	
	CPX	#dummy
	BLO 	bucle

fin	bra	fin



	ORG	vec
	DB	1,2,3,4,5,0,0,5,8,0,1,2,3,4,5,0,0,5,8,0