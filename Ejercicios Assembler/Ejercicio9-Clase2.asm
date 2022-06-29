*recorro un vector de elementos de 8 bits 
*
*
RWM	EQU	0
ROM	EQU	$C000
valores EQU	20
	
	ORG	RWM
ceros	RMB	1
vec	RMB	valores
cont 	RMB	1	
	
	ORG	ROM

	CLR 	ceros	
	LDX	#(vec+valores)
bucle	LDAA 	0,x
	BNE	noCero
	INC	ceros
noCero	DEX	
	CPX	#vec ;Compara X con memoria, hace IX - 20
	BHS 	bucle

fin	bra	fin



	ORG	vec
	DB	1,2,3,4,5,0,0,5,8,0,1,2,3,4,5,0,0,5,8,0