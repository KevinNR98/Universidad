*
*
*
RWM	EQU	0
ROM	EQU	$C000

	
	ORG	RWM
dirini	RMB	2
ceros	RMB	1
	
	ORG	ROM	
	LDX	dirini
	LDX	#dirini		<-este no va
fin	bra	fin

	
	ORG	RWM
	DB	0,$20

	ORG	$0020	
	DB	1,2,3,4,5,0,0,5,8,0,1,2,3,4,5,0,0,5,8,0