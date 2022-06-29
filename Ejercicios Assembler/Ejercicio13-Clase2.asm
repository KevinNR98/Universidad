*recorro un vector de elementos de 16 bits 
*y cuento las ocurrencias de un valor objetivo


RWM		EQU	0
ROM		EQU	$C000


		ORG	RWM
vector		DW	$9999,$1234,$4444,$90,$1234,$4312,$5678,9090	*esto en RWM no tiene sentido
cantidad 	RMB	1
objetivo	FDB	$1234		*esto en RWM no tiene sentido


		ORG	ROM
		CLR	cantidad
		LDX	#vector
		LDD	objetivo
loop		CPD 	0,x
		BNE	noSosVo
		INC	cantidad
noSosVo
		INX	
		INX 	;incremento dos veces por que estamos en 16 bits
		CPX	#cantidad	;aprovecho que tengo una reserva a cont. del vector
		BLO	loop
fin		BRA	fin