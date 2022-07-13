;;;ATOI : convierte una cadena de caracteres a una variable entera		
			ORG	$0000
			db	'e,'F


			ORG	$c000
inicio
			ldaa	$00
			cmpa	#'9
			bhi	esletrah
			suba	#$30
			bra	storeh
esletrah			
			anda	#%11011111
			suba  #$37
storeh
			tab ; transfiero REG a _>> Reg B

			lslb
			lslb
			lslb
			lslb

			ldaa	$01
			cmpa	#'9
			bhi	esletral
			suba	#$30
			bra	storel
esletral
			anda	#%11011111
			suba	#$37
storel
			aba
			staa	$02

fin			bra	fin




			ORG	$fffe
			dw	inicio