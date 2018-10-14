	TRIANGULO: EQU 1
SECTION TEXT
		INPUT		B ;Danielle almeida lima
		INPUT		H
		LOAD		B
		MULT		H ;kakakakak
		IF TRIANGULO
		DIV		dois
		Store		R
		Output	R
		STOP
SECTION BSS
	B:		SPACE ;feliz
	H:		SPACE ; lalalalal
	R:		SPACE
	SECTION DATA
	DOIS:	CONST		2
