ROM        	EQU     $C000
RAM        	EQU     $0000

TAM		EQU   	64
NUMERO		EQU 	1
TAMCONT	EQU	2	

	      	ORG  	RAM
VECTOR  	RMB   	TAM
CONTADOR	RMB	TAMCONT

        ORG     ROM

      	LDS   	#$00FF
      	LDX   	#VECTOR
	CLR	CONTADOR
	CLR	CONTADOR+1
      	CLRA
      	CLRB

MAIN
    	JSR    CONTNCANT
FIN	BRA     FIN

CONTNCANT
SIGUE	
	LDY	#NUMERO
    	LDD   	0,X
	BEQ   	LEE0       	SALTA SI ES 0
	CPY	0,X
	BNE   	DISTINTOS
	INX
	INX
	BRA	SIGUE

DISTINTOS
	INC	CONTADOR+1
	INX
	INX
	BRA	SIGUE

LEE0	
	LDX	CONTADOR	CARGA X CON EL DATO DE CONTADOR
    	RTS

    ORG     VECTOR

	DW    2,3,3,2,0