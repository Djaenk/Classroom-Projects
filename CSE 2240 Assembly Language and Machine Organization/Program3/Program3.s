				AREA Program3,CODE,READONLY
pointer			RN		0
				ENTRY
				ADR		pointer,sourceArray
				CMP		r2,temp,#1
				ADDEQ
				
				END
sourceArray		DCB		2,4,6,6,0,1,4,8,3,0,3,1,2,2,5,2,2,3,8,1
				DCB		9,1,5,3,4,2,6,7,8,9,0,4,4,3,2,3,6,5,4,5,6,7
				DCB		4,1,2,1,4,6,7,6,3,3,2,6,8,9,9,9,1,4,2,3,4,5
sourceArraySize	DCB		0x40