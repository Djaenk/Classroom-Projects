`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/11/2019 11:55:24 AM
// Design Name: 
// Module Name: if_statement
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


module if_statement(
    F,A,B,C,D,S[1:0]
    );
    input wire A,B,C,D;
    input wire [1:0] S;
    output reg F;
    
    always @(*) begin
        if(S == 0)
            F = A;
        if(S == 1)
            F = B;
        if(S == 2)
            F = C;
        if(S == 3)
            F = D;
    end

endmodule
