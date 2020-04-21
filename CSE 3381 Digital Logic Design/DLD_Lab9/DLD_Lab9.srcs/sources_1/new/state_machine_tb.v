`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/06/2019 11:35:17 AM
// Design Name: 
// Module Name: state_machine_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module state_machine_tb(

    );
reg [3:0] state;
wire [3:0] next_state;
wire [15:0] one_hot;
reg clock;
reg reset;

initial
clock = 1'b0;
always
begin
    state = next_state;
    clock = ~clock;
    #20;
end

decoder state_machine(clock, reset, state, one_hot, next_state);
initial
begin
state = 0;
reset = 0;
$monitor(state, next_state, one_hot, reset);
#310
reset = 1;
#50
reset = 0;
#200
reset = 1;
#25
reset = 0;
end
endmodule
