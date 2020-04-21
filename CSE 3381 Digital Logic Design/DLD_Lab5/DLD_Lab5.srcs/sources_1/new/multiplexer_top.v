`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/11/2019 12:02:59 PM
// Design Name: 
// Module Name: multiplexer_top
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


module multiplexer_top(
    led, sw[15:0]
    );
    input [15:0] sw;
    output led;
    
    case_statement multiplexer(led, sw[15], sw[14], sw[13], sw[12], sw[1:0]);
endmodule
