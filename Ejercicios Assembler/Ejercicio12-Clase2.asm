*recorro un vector de elementos de 8 bits 
*los ceros, los negativos, y los multiplos de 8
*
RWM	EQU	0
ROM	EQU	$C000
valores EQU	19
	
	ORG	RWM
cantC	RMB	1	*sugerencia: plantearlo para +255 ocurrencias
cantN	RMB	1
cant8	RMB	1
dirIni	RMB	2	*aqui tenemos la direccion inicial(NO EL VECTO!	)
dirFin	RMB	2	*ATTENTI! guardo las direcciones en 2 bytes
	
	ORG	ROM
*pongo en cero los contadores de cosas
	CLR 	cantC
	CLR 	cantN
	CLR 	cant8

	LDX	dirIni
bucle	LDAA 	0,x
	BNE	noCero
	INC	cantC	*actualiza el flag N
noCero
	CMPA	#0
	BPL	noNeg	*salta si N=0
	INC	cantN
noNeg
	ANDA	#%00000111
	BNE	noMu18
	INC	cant8
noMu18
	INX
	CPX	dirFin
	BLS	bucle
fin	BRA	fin




	ORG	$0030
	DB	1,2,3,4,5,0,0,-5,8,0,1,-2,3,-4,5,16,0,5,8,0