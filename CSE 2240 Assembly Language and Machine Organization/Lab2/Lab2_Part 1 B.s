				AREA Lab2Part1B,CODE,READONLY
index			RN		r1
pointer			RN		r2
character		RN		r3
				ENTRY
				ADR		pointer,String
				MOV		index,#0
Iterate
				LDRB	character,[pointer,index]
				CMP		character,#0x20
				ADDEQ	index,index,#1
				BEQ		Iterate
Stop			B		Stop
String 			DCB 	"                         Hello, World",0x0D
				END