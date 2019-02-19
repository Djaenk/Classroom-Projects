		AREA Program1,CODE,READONLY
		ENTRY
		LDR		r1,C
		LDR		r2,D
		LDR		r3,E
		LDR		r4,F
		MVN		r5,r1
		ADD		r5,r5,#1
		MVN		r6,r3
		ADD		r7,r2,r5
		ADD		r8,r4,r6
		MUL		r9,r8,r8
		MUL		r10,r7,r9
		LSR		r0,r10,#4
stop	B	stop
		
C		DCD     234
D		DCD     401
E       DCD     9
F       DCD     100
		END