				AREA Program4,CODE,READONLY
pointer			RN		r0
N				RN		r1
i				RN		r2
p				RN		r3
pp				RN		r4
bool			RN		r5
				ENTRY
				MOV		N,#100
				LDR		pointer,=0x40000000
Initialize				
				MOV		i,#0
				MOV		bool,#1
InitializeBody	STRB	bool,[pointer,i]
				ADD		i,i,#1
				CMP		i,N
				BLE		InitializeBody
Sieve
				MOV		p,#2
SieveBody		LDRB	bool,[pointer,p]
				CMP		bool,#1
				BNE		SiftElse
Sift			
				ADD		i,p,p
				MOV		bool,#0
SiftBody		STRB	bool,[pointer,i]
				ADD		i,i,p
				CMP		i,N
				BLE		SiftBody
SiftElse		ADD		p,p,#1
				MUL		pp,p,p
				CMP		pp,N
				BLE		SieveBody
CollectPrimes
				MOV		i,N
				MOV		p,#2
CollectBody		LDRB	bool,[pointer,p]
				CMP		bool,#1
				BNE		CollectElse
				STR		p,[pointer,i,LSL #2]
CollectElse		ADD		p,p,#1
				ADD		i,i,#1
				CMP		p,N
				BLE		CollectBody
Stop			B		Stop
				END