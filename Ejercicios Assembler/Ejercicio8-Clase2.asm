*recorro un vector de elementos de 8 bits 
*
*
RWM	EQU	0
ROM	EQU	$C000
valores EQU	20
	
	ORG	RWM
ceros	RMB	1
vec	RMB	valores

	
	ORG	ROM

	CLR	ceros	
	LDX	#vec ;Obtengo la direccion de vec en modo inmediato
bucle	LDAA 	0,x
	BNE	noCero
	INC	ceros
noCero	INX	
	
	DECB
	BNE

fin	bra	fin



	ORG	RWM
	DB	1,2,3,4,5,0,0,5,8,0,1,2,3,4,5,0,0,5,8,0