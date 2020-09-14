		AREA Program1,CODE,READONLY
		ENTRY
		LDR		r1,C
		LDR		r2,D
		LDR		r3,E
		LDR		r4,F
		MVN		r1,r1
		ADD		r1,r1,#1	;r1 holds -C
		MVN		r3,r3
		ADD		r3,r3,#1	;r3 holds -E
		ADD		r5,r1,r2	;r5 holds (-C + D)
		ADD		r6,r3,r4	;r6 holds (F - E)
		MUL		r7,r6,r6	;r7 holds (F - E)^2	
		MUL		r8,r5,r7	;r8 holds ((-C + D) * (F - E)^2)
		LSR		r0,r8,#4	;via LSR by four bits, r0 holds ((-C + D) * (F - E)^2) / 16
stop		B		stop
		
C		DCD     234
D		DCD     401
E       	DCD     9
F       	DCD     100
		END
