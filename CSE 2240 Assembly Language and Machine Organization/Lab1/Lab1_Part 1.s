				AREA Lab1Part1,CODE,READONLY
				ENTRY
				MOV		r1,#22		;X
				MOV		r2,#17		;Y
				MOV		r3,#95		;Z
				MOV		r4,#8
				MUL		r5,r2,r4	;8Y
				MOV		r6,#7
				MUL		r7,r3,r6	;7Z
				ADD		r0,r1,r5
				ADD		r0,r0,r7
				SUB		r0,r0,#27
				LSR		r0,#3				;result of evaluation stored in register 0
stop			B		stop
				END