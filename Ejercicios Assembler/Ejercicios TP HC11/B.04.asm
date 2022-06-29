;;Valores constantes 
variableB	EQU 6
variableC	EQU 2
variableD	EQU 3
variableE	EQU 2
variableF	EQU 2


RAM		EQU 	$0000
ROM		EQU 	$C000

		ORG  	RAM
variableA	RMB	2		

		ORG	ROM
		CLR	variableA

		LDAA 	#variableF
		LDAB	#variableE
		ABA
		STAA	variableA
		LDAA	#variableD
		LDAB	#2
		SBA
		LDAB	variableA
		MUL
		STD	variableA
		LDX	variableA
		
		LDAA	#variableB
		LDAB	#variableB
		MUL	
		STAB	variableA

		LDAA	#variableC
		LDAB	#variableC
		MUL
		LDAA	#variableC
		MUL
		LDAA 	variableA
		SBA
		TAB
		CLRA
		CLR	variableA
		IDIV
		XGDX
		STD	variableA
FIN		BRA	FIN				
		
		
		
		
		
		
		
		
			
		
				