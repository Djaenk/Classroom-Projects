`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/11/2019 12:07:24 PM
// Design Name: 
// Module Name: multiplexer_tb
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


module multiplexer_tb(

    );
    reg [3:0] I;
    reg [1:0] S;
    wire F;
    
    always_block testbench(F,I[3:0],S[1:0]);
    
    initial begin
        $monitor(F,I[3:0],S[1:0]);

        I[0] = 0;
        I[1] = 0;
        I[2] = 0;
        I[3] = 0;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
    
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;

        I[0] = 0;
        I[1] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 0;
        I[1] = 0;
        I[2] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 0;
        I[1] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 0;
        I[1] = 0;
        I[2] = 0;
        I[3] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 0;
        I[1] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 0;
        I[1] = 0;
        I[2] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 0;
        I[1] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
        
        I[0] = 1;
    #15 S = 2'b00;
    #15 S = 2'b01;
    #15 S = 2'b10;
    #15 S = 2'b11;
    end
endmodule