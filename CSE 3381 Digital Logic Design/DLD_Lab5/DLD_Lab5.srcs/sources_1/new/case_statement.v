`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/11/2019 11:57:55 AM
// Design Name: 
// Module Name: case_statement
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


module case_statement(
    F,A,B,C,D,S[1:0]
    );
    input wire A,B,C,D;
    input wire [1:0] S;
    output reg F;
    
    always @(*) begin
        case (S)
            2'b00  : F <= A;
            2'b01  : F <= B;
            2'b10  : F <= C;
            2'b11  : F <= D;
        endcase
    end
endmodule
