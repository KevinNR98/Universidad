* Ejercicio del TP 3 (B.02)

INICIO  CLRA
	LDAB $F5
Otro	ADDA $F7
	DECB	*Decrementa el acumulador B en 1
	BNE  otro *pregunta si el resultado es dio 0
	STAA $F8
FIN	BRA  FIN

*El programa carga los datos 00F5=08 y 00F7=12 en el inicio, y una vez
*Cargados en memeria a B lo va a ir decrementando hasta que se cumpla BNE
*Al mismi tiemo que a f7 se le va a ir sumando 12 cada vez que vuelva hacia
*Atras el programa