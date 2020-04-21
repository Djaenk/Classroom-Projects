`timescale 1ns / 1ps

module three_bit_adder(A,B,C_in,S,C_out);
input [2:0] A,B;
input C_in;
wire C1,C2;
output [2:0] S;
output C_out;
full_adder adder1(A[0],B[0],C_in,S[0],C1);
full_adder adder2(A[1],B[1],C1,S[1],C2);
full_adder adder3(A[2],B[2],C2,S[2],C_out);
endmodule
