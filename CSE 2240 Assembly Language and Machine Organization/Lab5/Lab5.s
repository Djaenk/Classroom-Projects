				AREA	Lab5,CODE,READONLY
pointer			RN		r0
last			RN		r1
pairs			RN		r2
temp			RN		r3
index			RN		r4
index_inc		RN		r7
num				RN		r10
writeto			RN		r11
				ENTRY
				ADR		pointer,items
				MOV		num,#20
				LDR		writeto,=0x40000000
				MOV		last,num
				MOV		index,#0
Write			CMP		index,num
				BGE		Sort
				LDR		r5,[pointer,index,LSL #2]
				STR		r5,[writeto,index,LSL #2]
				ADD		index,index,#1
				B		Write
Sort			CMP		last,#0
				BLE		Sorted
				SUB		pairs,last,#1
				MOV		index,#0
For				CMP		index,pairs
				BGT		Sort
				ADD		index_inc,index,#1
				LDR		r5,[writeto,index,LSL #2]
				LDR		r6,[writeto,index_inc,LSL #2]
				CMP		r5,r6
				BLT		NoSwap
Swap			MOV		temp,r5
				MOV		r5,r6
				MOV		r6,temp
				MOV		last,index
				STR		r5,[writeto,index,LSL #2]
				STR		r6,[writeto,index_inc,LSL #2]
NoSwap			ADD		index,index,#1
				B		For
Sorted			B		Sorted
items			DCD		2,4,3,33,54,6,-5,2,0,1,1,2
				DCD		98,9,8,4,0,-9,4,-49
				END