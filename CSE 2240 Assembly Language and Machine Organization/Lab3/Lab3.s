				AREA	Lab3,CODE,READONLY
loadPointer		RN		r0
memPointer		RN		r1
char			RN		r2
				ENTRY
				ADR		loadPointer,string
				LDR		memPointer,=0x40000000
Loop			LDRB	char,[loadPointer],#1
				CMP		char,#0x0D
				BEQ		Stop
				CMP		char,#0x61
				BLT		write
				CMP		char,#0x7a
				BGT		write
capitalize		AND		char,char,#2_01011111
write			STRB	char,[memPointer],#1
				B		Loop
Stop			B		Stop
string			DCB		"Anthony Wang",0x0D
				END