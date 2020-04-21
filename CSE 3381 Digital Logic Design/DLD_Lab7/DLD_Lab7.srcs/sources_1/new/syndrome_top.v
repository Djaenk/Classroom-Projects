module encode_top(sw, led);
    input [10:0] sw;
    output [15:0] led;
    
    decode Hamming(led[6:0], led[15:12], sw);
endmodule