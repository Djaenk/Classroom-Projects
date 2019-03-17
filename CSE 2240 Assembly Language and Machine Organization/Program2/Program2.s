				AREA Program2,CODE,READONLY
randomInteger	RN		0
pointer			RN		1
counter			RN		2
constant1		RN		3
constant2		RN		4
constant3		RN		5
temp			RN		6
				ENTRY
				LDR		randomInteger,=0x13245099
				LDR		pointer,=0x40000000
				MOV		counter,#20
				LDR		constant1,=214013
				LDR		constant2,=2531011
				LDR		constant3,=0x7FFF
loop			MUL		temp,randomInteger,constant1
				ADD		temp,temp,constant2
				LSR		randomInteger,temp,#16
				AND		randomInteger,constant3
				STRH	randomInteger,[pointer]
				ADD		pointer,pointer,#2
				SUBS	counter,#1
				BNE		loop
stop			B		stop
				END