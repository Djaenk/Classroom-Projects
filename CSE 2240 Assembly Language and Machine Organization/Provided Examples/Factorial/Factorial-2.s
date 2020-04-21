;Page 51 of Hohl text
;int main() {
;     int n = 4;       //r6
;     int result = 1;  //r7
;     while(n > 0) {
;        result = result * n;
;        n--;
;     }
;     cout << result;
;} 
		AREA	FactorialCalculation,CODE,READONLY
		ENTRY
Version1
		MOV		r6,#4		;Find factorial of 4
		MOV		r7,#1		;if n=0, at least n!=1
loop1	CMP		r6,#0
        BEQ     Version2
		MUL	    r7,r6,r7		
		SUB	    r6,r6,#1	;decrement n
		B		loop1		;do another MUL if counter > 0

Version2
		MOV		r6,#4		;Find factorial of 4
		MOV		r7,#1		;if n=0, at least n!=1
loop2	CMP		r6,#0
		MULGT	r7,r6,r7		
		SUBGT	r6,r6,#1	;decrement n
		BGT		loop2		;do another MUL if counter > 0
		
stop	B		stop		;loop forever (r7 contains n!)
		END
		