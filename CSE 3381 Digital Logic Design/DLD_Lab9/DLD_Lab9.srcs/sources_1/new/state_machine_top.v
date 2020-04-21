`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/06/2019 12:26:11 PM
// Design Name: 
// Module Name: state_machine_top
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


module state_machine_top(
    clk,
    sw,
    led
    );
input clk;
input wire [0:0] sw;
output wire [15:0] led;
wire [3:0] state;
wire [3:0] next_state;

wire clock;
divider counter(clk, next_state, clock, state);

decoder state_machine(clock, sw, state, led, next_state);

endmodule
