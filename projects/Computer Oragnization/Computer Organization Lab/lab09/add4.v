`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:25:35 04/17/2011 
// Design Name: 
// Module Name:    add4 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module ADD_4(A,B,Cin,m,S,CF,OF);//4Î»¼Ó·¨Æ÷
	input wire [3:0] A,B;
	input wire Cin,m;
	output wire [3:0] S;
	output wire CF,OF;
	
	wire [3:0] xb,p,g;
	wire [4:0] c;
	
	xor(xb[0],B[0],m);xor(xb[1],B[1],m);
	xor(xb[2],B[2],m);xor(xb[3],B[3],m);
	
	and(g[0],A[0],xb[0]);and(g[1],A[1],xb[1]);
	and(g[2],A[2],xb[2]);and(g[3],A[3],xb[3]);
	
	or(p[0],A[0],xb[0]);or(p[1],A[1],xb[1]);
	or(p[2],A[2],xb[2]);or(p[3],A[3],xb[3]);
	
	assign c[0]=Cin;
	assign c[1]=g[0]|(p[0]&c[0]);
	assign c[1] = g[0]|(p[0]&c[0]);
   assign c[2] = g[1]|(p[1]&g[0])|(p[1]&p[0]&c[0]);
   assign c[3] = g[2]|(p[2]&g[1])|(p[2]&p[1]&g[0])|(p[2]&p[1]&p[0]&c[0]);
   assign c[4] = g[3]|(p[3]&g[2])|(p[3]&p[2]&g[1])|(p[3]&p[2]&p[1]&g[0])|(p[3]&p[2]&p[1]&p[0]&c[0]); 
	
	assign S[3:0]={A[3]^xb[3]^c[3],A[2]^xb[2]^c[2],A[1]^xb[1]^c[1],A[0]^xb[0]^c[0]};
	
	assign CF=c[4];
	xor(OF,c[4],c[3]);

endmodule

