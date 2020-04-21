				AREA Lab1Part2,CODE,READONLY
				ENTRY
				LDR		r1,X
				LDR		r2,Y
				LDR		r3,Z
				MOV		r4,r1,LSR #9
				MOV		r5,r2,LSR #1
				MOV		r6,r3,LSR #5
				AND		r4,r4,#2_0000000000111111
				AND		r5,r5,#2_0000000000111111
				AND		r6,r6,#2_0000000000111111
				ADD		r7,r4,r5
				EOR		r0,r6,r7				;result of operation stored in register 0
stop			B		stop
X				DCW		2_0010000011110010
Y				DCW		2_0011000011110000
Z				DCW		2_1100010011111000
				END