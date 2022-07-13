;;;ITOA:se utiliza para convertir un valor numérico en una cadena de texto	
			ORG	$0000
			db	$F5


			ORG	$c000
inicio

			ldaa	$00
			lsra
			lsra
			lsra
			lsra
			cmpa	#$9
			bls	esnumero_h
			adda	#$07
esnumero_h
			adda	#$30
			staa	$01

			ldaa	$00
			anda	#$0f
			cmpa	#$9
			bls	esnumero_l
			adda	#7
esnumero_l
			adda	#$30
			staa	$02








fin			bra	fin

			ORG	$fffe
			dw	inicio