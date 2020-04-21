				AREA Program3,CODE,READONLY
counter			RN		0
arrayPointer	RN		1
countPointer	RN		2
size			RN		3
index			RN		4
comparand		RN		5
value			RN		6
				ENTRY
				ADR		arrayPointer,sourceArray
				LDR		countPointer,=0x40000000
				LDR		size,sourceArraySize
				MOV		comparand,#0								;initialize comparand to 0
Loop																;loop over the array for each digit 0 through 9
				MOV		counter,#0									;reset counter
				MOV		index,#0									;reset index
Iterate																;iterate through the array
				LDRB	value,[arrayPointer,index]					;load byte from sourceArray at appropriate index
				CMP		value,comparand
				ADDEQ	counter,counter,#1							;if value and comparand are equal, increment counter
				ADD		index,index,#1								;increment index
				CMP		index,size
				BLT		Iterate										;if index is within array bound, iterate over next value

				STR		counter,[countPointer,comparand,LSL #2]		;store the count to memory at appropriate index of count array
				ADD		comparand,comparand,#1						;increment comparand
				CMP		comparand,#9
				BLE		Loop										;if comparand is less than 9, loop through sourceArray again

stop			B		stop

sourceArray		DCB		2,4,6,6,0,1,4,8,3,0,3,1,2,2,5,2,2,3,8,1
				DCB		9,1,5,3,4,2,6,7,8,9,0,4,4,3,2,3,6,5,4,5,6,7
				DCB		4,1,2,1,4,6,7,6,3,3,2,6,8,9,9,9,1,4,2,3,4,5
sourceArraySize	DCB		0x40
				END