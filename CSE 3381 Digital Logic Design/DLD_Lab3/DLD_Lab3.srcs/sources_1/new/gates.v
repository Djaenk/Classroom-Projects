`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/27/2019 11:14:50 AM
// Design Name: 
// Module Name: gates
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
module gates_top(sw,led);
input wire [15:0] sw;
output wire [2:0] led;

wire [2:0] A,B,C,D,F;
assign A[0] = sw[15];
assign A[1] = sw[14];
assign A[2] = sw[13];
assign B[0] = sw[12];
assign B[1] = sw[11];
assign B[2] = sw[10];
assign C[0] = sw[9];
assign C[1] = sw[8];
assign C[2] = sw[7];
assign D[0] = sw[6];
assign D[1] = sw[5];
assign D[2] = sw[4];
assign F[0] = led[0];
assign F[1] = led[1];
assign F[2] = led[2];

multigate(A,B,C,D,sw[1],sw[0],F);
endmodule

module multigate(a,b,c,d,s1,s2,f);
input [2:0] a,b,c,d;
wire [2:0] andf,orf,nandf,norf;
wire [2:0] f0,f1,f2,f3;
input s1,s2;
output [2:0] f;

and (andf[0], a[0],b[0],c[0],d[0]);
and (andf[1], a[1],b[1],c[1],d[1]);
and (andf[2], a[2],b[2],c[2],d[2]);
or  (orf[0],  a[0],b[0],c[0],d[0]);
or  (orf[1],  a[1],b[1],c[1],d[1]);
or  (orf[2],  a[2],b[2],c[2],d[2]);
nand(nandf[0],a[0],b[0],c[0],d[0]);
nand(nandf[1],a[1],b[1],c[1],d[1]);
nand(nandf[2],a[2],b[2],c[2],d[2]);
nor (norf[0], a[0],b[0],c[0],d[0]);
nor (norf[1], a[1],b[1],c[1],d[1]);
nor (norf[2], a[2],b[2],c[2],d[2]);

and (f0[0],~s1,~s2,andf[0]);
and (f1[0],~s1, s2,orf[0]);
and (f2[0], s1,~s2,nandf[0]);
and (f3[0], s1, s2,norf[0]);
and (f0[1],~s1,~s2,andf[1]);
and (f1[1],~s1, s2,orf[1]);
and (f2[1], s1,~s2,nandf[1]);
and (f3[1], s1, s2,norf[1]);
and (f0[2],~s1,~s2,andf[2]);
and (f1[2],~s1, s2,orf[2]);
and (f2[2], s1,~s2,nandf[2]);
and (f3[2], s1, s2,norf[2]);

or  (f[0],f0[0],f1[0],f2[0],f3[0]);
or  (f[1],f0[1],f1[1],f2[1],f3[1]);
or  (f[2],f0[2],f1[2],f2[2],f3[2]);
endmodule
