`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/01/2019 11:30:20 AM
// Design Name: 
// Module Name: syndrome
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


module decode(data, syndrome, code);
    input [10:0] code;
    output [3:0] syndrome;
    output [6:0] data;
    reg [10:0] corrected;
    
    always @*
        corrected = code;

    assign syndrome[0] = code[0] ^ code[2] ^ code[4] ^ code[6] ^ code[8] ^ code[10];
    assign syndrome[1] = code[1] ^ code[2] ^ code[5] ^ code[6] ^ code[9] ^ code[10];
    assign syndrome[2] = code[3] ^ code[4] ^ code[5] ^ code[6];
    assign syndrome[3] = code[7] ^ code[8] ^ code[9] ^ code[10];
    
    always @*
        if (syndrome != 0)
            corrected[syndrome - 1] = ~code[syndrome - 1];    
    
    assign data[0] = code[2];
    assign data[1] = code[4];
    assign data[2] = code[5];
    assign data[3] = code[6];
    assign data[4] = code[8];
    assign data[5] = code[9];
    assign data[6] = code[10];
endmodule
