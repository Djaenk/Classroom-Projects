`timescale 1ns / 1ps

module full_adder(A,B,C_in,S,C_out);
input A,B,C_in;
wire C1,C2,S1;
output C_out,S;
half_adder halfadder1(A,B,C1,S1);
half_adder halfadder2(S1,C_in,C2,S);
or(C_out,C1,C2);
endmodule
