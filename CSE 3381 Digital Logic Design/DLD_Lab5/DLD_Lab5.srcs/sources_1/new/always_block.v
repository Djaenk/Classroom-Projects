`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/11/2019 11:17:17 AM
// Design Name: 
// Module Name: always_block
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


module always_block(
    F,I,S[1:0]
    );
    input [3:0] I;
    input [1:0] S;
    output reg F;
    
    always @(*) begin
        F = I[S];
    end
    
endmodule
