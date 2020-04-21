`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/22/2019 12:28:55 PM
// Design Name: 
// Module Name: decoder
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


module decoder(
    input clk,
    input rst,
    input wire [3:0] state,
    output reg [15:0] one_hot,
    output reg [3:0] next_state
    );
    
always @(posedge clk or posedge rst)
begin
    if (state[3] == 0)
    begin
        one_hot[12] <= 0;
        one_hot[8] <= 0;
        one_hot[7:4] <= 4'b0001;
        one_hot[3:0] <= 4'b0001;
        if (state[2] == 0)
        begin
            one_hot[15] <= 0;
            one_hot[14] <= ~&state[1:0];
            one_hot[13] <= &state[1:0];
            one_hot[11] <= 0;
            one_hot[10] <= ~&state[1:0];
            one_hot[9] <= &state[1:0];
        end
        else
        begin
            one_hot[15:12] <= 4'b1000;
            one_hot[11:8] <= 4'b1000;
        end
    end
    else
    begin
        one_hot[15:12] <= 4'b0001;
        one_hot[11:8] <= 4'b0001;
        one_hot[4] <= 0;
        one_hot[0] <= 0;
        if (state[2] == 0)
        begin
            one_hot[7] <= 0;
            one_hot[6] <= ~&state[1:0];
            one_hot[5] <= &state[1:0];
            one_hot[3] <= 0;
            one_hot[2] <= ~&state[1:0];
            one_hot[1] <= &state[1:0];
        end
        else
        begin
            one_hot[7:4] <= 4'b1000;
            one_hot[3:0] <= 4'b1000;
        end
    end

    if(rst)
    begin
        next_state <= 4'b1111;
        one_hot <= 16'b0001000100010001;
    end
    else
    begin
        if(state[2] == 1)
            next_state = state + 4;
        else
            next_state = state + 1;
    end
end
endmodule
