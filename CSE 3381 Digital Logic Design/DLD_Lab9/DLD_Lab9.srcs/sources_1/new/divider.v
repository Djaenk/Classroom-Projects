`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/22/2019 12:19:32 PM
// Design Name: 
// Module Name: divider
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


module divider(
    input clk,
    input wire [3:0] next_state,
    output reg clk_divider,
    output reg [3:0] state
    );
reg [31:0] count;
always @ (posedge(clk))
begin
    if (count == 250000000 - 1)
    begin
        count <= 32'b0;
        clk_divider <= ~clk_divider;
        state <= next_state;
    end
    else
        count <= count + 1;
end
endmodule
