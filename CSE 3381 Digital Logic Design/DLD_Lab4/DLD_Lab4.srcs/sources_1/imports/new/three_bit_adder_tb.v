`timescale 1ns / 1ps

module three_bit_adder_tb();
reg [2:0] A,B;
reg C_in;
wire [3:0] S;

three_bit_adder add(A,B,C_in,S[2:0],S[3]);

initial
begin
$monitor(A,B,C_in,S);

A = 3'b000;
B = 3'b000;
C_in = 1'b0;

#100

A = 3'b111;
B = 3'b111;
C_in = 1'b1;

#100

A = 3'b101;
B = 3'b010;
C_in = 1'b1;

end
endmodule
