				AREA	Program5,CODE,READONLY
				ENTRY
index1			RN		r8
index2			RN		r9
lower1			RN		r4
upper1			RN		r5
lower2			RN		r6
upper2			RN		r7
				LDR 	sp, =0x40000200
				ADR		r1,sourceArray
				LDR		r2,=tsize
				LDR		r3,=0x40001000
				BL		copyArray
				STMDB	sp!,{r0,r3}
				BL		sumArray
Stop			B		Stop
								
copyArray		
				STMDB	sp!,{r4-r12,lr}
				MOV		r10,r3
				MOV		index1,#0
LoadFor			CMP		index1,r2
				BGE		exitLoad
				LDMIA	r1!,{lower1,upper1}
				MOV		index2,#0
				MOV		r11,r3
CompareFor		CMP		index2,index1
				BGE		exitCompare
				LDMIA	r11!,{lower2,upper2}
				CMP		lower1,lower2
				BNE		passComparison
				CMP		upper1,upper2
				BNE		passComparison
				B		failComparison
passComparison	ADD		index2,index2,#1
				B		CompareFor
exitCompare		STMIA	r10!,{lower1,upper1}
failComparison	ADD		index1,index1,#1
				B		LoadFor
exitLoad		SUB		r0,r10,r3
				LSR		r0,#3
				LDMIA	sp!,{r4-r12,pc}
				
sumArray
				STMDB	sp!,{lr}
				LDMIA	sp!,{r2,r3,r4}
				STMDB	sp!,{r4-r12}
				MOV		r0,#0
				MOV		r1,#0
				MOV		r10,r4
				MOV		index1,#0
SummationLoop	CMP		index1,r3
				BGE		exitSummation
				LDM		r10!,{lower1,upper1}
				ADDS	r1,r1,lower1
				ADC		r0,r0,upper1
				ADD		index1,index1,#1
				B		SummationLoop
exitSummation	LDMIA	sp!,{r4-r12}
				BX		r2

sourceArray		DCQ   0x0200200AD00236DD
				DCQ   0x00003401AAC4D097
				DCQ   0x0200200AD00236DD
				DCQ   0x00010AA0AD3C66DF
				DCQ   0x0000FC3D76400CCB
				DCQ   0x000090045ACDD097
				DCQ   0x00000FF000004551
				DCQ   0x0200200AD00236DD
				DCQ   0x003AC401AAC4D097
				DCQ   0x000090045ACDD097
				DCQ   0x09990AA0AD3C66DF
				DCQ   0x1000200AD00236DD
				DCQ   0x00003401AAC4D097
				DCQ   0x000001102ACFF200
				DCQ   0x00010AA0AD3C66DF
				DCQ   0x003AC401AAC4D097
				DCQ   0x1000FC3D76400CCB
				DCQ   0x000090045ACDD097
				DCQ   0x00000FF000004551
				DCQ   0x00000000003C66DF
				DCQ   0x0200200AD00236DD
				DCQ   0x00003401AAC4D097
				DCQ   0x000001102ACFF200
endArr
tsize			EQU   ((endArr-sourceArray)/8)
				END