`timescale 1ns / 1ps

module three_bit_adder_top(sw,led);
input wire [15:0] sw;
output wire [3:0] led;
wire [2:0] A,B;
wire C_in;
assign A[0] = sw[11];
assign A[1] = sw[12];
assign A[2] = sw[13];
assign B[0] = sw[7];
assign B[1] = sw[8];
assign B[2] = sw[9];
assign C_in = sw[15];
three_bit_adder adder(A,B,C_in,led[2:0],led[3]);
endmodule
