				AREA	Lab4,CODE,READONLY
LED_NUM			RN		r0
AD_val			RN		r1
num				RN		r2
dir				RN		r3
APB2ENR			RN		r4
CRH				RN		r5
BSRR			RN		r6
LSLindex		RN		r7
i				RN		r8
pointer			RN		r12
				ENTRY
				MOV		LED_NUM,#8
				MOV		AD_val,#2_0100
				MOV		num,#-1
				MOV		dir,#1
				MOV		APB2ENR,#2_1010
				ORR		APB2ENR,APB2ENR,#2_1000000
				LDR		CRH,=0x33333333
				LDR		r10,=100000
				MOV		r11,#15
				LDR		pointer,=0x40000000
Loop			
				ADD		num,num,dir
if				CMP		num,LED_NUM
				BLT		elseif
				MOV		dir,#-1
				SUB		num,LED_NUM,#1
				B		exitif
elseif			CMP		num,#0
				BGE		exitif
				MOV		dir,#1
				MOV		num,#0
exitif			SUB		LSLindex,r11,num
				MOV		BSRR,#1
				LSL		BSRR,LSLindex
for				MOV		i,#0
				LSL		r9,AD_val,#8
				ADD		r9,r9,r10
forbody			CMP		i,r9
				BHS		Loop
				LSL		BSRR,#16
				STR		BSRR,[pointer],#4
				LSR		BSRR,#16
				ADD		i,i,#1
				B		forbody
				END