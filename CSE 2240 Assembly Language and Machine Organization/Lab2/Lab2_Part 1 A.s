				AREA Lab2Part1A,CODE,READONLY
length			RN		r1
pointer			RN		r2
index			RN		r3
character		RN		r4
				ENTRY
				ADR		pointer,String
				MOV		index,#0
				MOV		length,#0
Iterate
				LDRB	character,[pointer,index]
				ADD		index,index,#1
				CMP		character,#0x0D
				ADDNE	length,length,#1
				BNE		Iterate
Stop			B		Stop
String			DCB		"CSE, Lyle School of Engineering",0x0D
				END