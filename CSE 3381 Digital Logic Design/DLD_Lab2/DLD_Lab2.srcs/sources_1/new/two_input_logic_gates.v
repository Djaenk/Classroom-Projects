module logic_gates_top(sw, led);
output [4:0] led;
input [1:0] sw;
two_input_logic_gates gates(sw[0], sw[1], led[0], led[1], led[2], led[3], led[4]);
endmodule

module logic_gates_tb();
reg input1,input2;
wire not_gate,and_gate,or_gate,nand_gate,xor_gate;
two_input_logic_gates gates(.a(input1), .b(input2), .v(not_gate), .w(and_gate), .x(or_gate), .y(nand_gate), .z(xor_gate));

initial
begin
$monitor(input1, input2, not_gate, and_gate, or_gate, nand_gate, xor_gate);
input1 = 1'b0;
input2 = 1'b0;
#5
input1 = 1'b0;
input2 = 1'b1;
#5 
input1 = 1'b1;
input2 = 1'b0;
#5
input1 = 1'b1;
input2 = 1'b1;
end
endmodule

module two_input_logic_gates(a,b,v,w,x,y,z);
input a,b;
output v,w,x,y,z;
not gate1(v,a);
and gate2(w,a,b);
or gate3(x,a,b);
nand gate4(y,a,b);
xor gate5(z,a,b);
endmodule