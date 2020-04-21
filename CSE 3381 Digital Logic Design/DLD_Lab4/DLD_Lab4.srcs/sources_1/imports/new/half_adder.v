`timescale 1ns / 1ps

module half_adder(A,B,C,S);
input A,B;
output C,S;
xor(S,A,B);
and(C,A,B);
endmodule