`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/25/2019 11:42:41 AM
// Design Name: 
// Module Name: Hamming code
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


module encode(code, data);
    input [6:0] data;
    output [10:0] code;

    assign code[2] = data[0];
    assign code[4] = data[1];
    assign code[5] = data[2];
    assign code[6] = data[3];
    assign code[8] = data[4];
    assign code[9] = data[5];
    assign code[10] = data[6];
    
    assign code[0] = code[2] ^ code[4] ^ code[6] ^ code[8] ^ code[10];
    assign code[1] = code[2] ^ code[5] ^ code[6] ^ code[9] ^ code[10];
    assign code[3] = code[4] ^ code[5] ^ code[6];
    assign code[7] = code[8] ^ code[9] ^ code[10];
endmodule
