`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:26:21 03/15/2011 
// Design Name: 
// Module Name:    adder_4bit 
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
module adder_4bit(A,B,Ci,S,Co);
	input wire [3:0] A,B;
	input wire Ci;
	output wire [3:0] S;
	output wire Co;
	
	wire [3:0] P, G;
	wire [3:1] C;
	wire Ta;
	wire [1:0] Tb;
	wire [2:0] Tc;
	wire [3:0] Td;
	
	adder_half a0(A[0],B[0],P[0],G[0]),
					a1(A[1],B[1],P[1],G[1]),
					a2(A[2],B[2],P[2],G[2]),
					a3(A[3],B[3],P[3],G[3]);
	
	and (Ta,P[0],Ci);
	and (Tb[0],P[1],G[0]);
	and (Tb[1],P[1],P[0],Ci);
	and (Tc[0],P[2],G[1]);
	and (Tc[1],P[2],P[1],G[0]);
	and (Tc[2],P[2],P[1],P[0],Ci);
	and (Td[0],P[3],G[2]);
	and (Td[1],P[3],P[2],G[1]);
	and (Td[2],P[3],P[2],P[1],G[0]);
	and (Td[3],P[3],P[2],P[1],P[0],Ci);
	
	or (C[1],G[0],Ta);
	or (C[2],G[1],Tb[0],Tb[1]);
	or (C[3],G[2],Tc[0],Tc[1],Tc[2]);
	or (Co,G[3],Td[0],Td[1],Td[2],Td[3]);
	
	xor (S[0],P[0],Ci);
	xor (S[1],P[1],C[1]);
	xor (S[2],P[2],C[2]);
	xor (S[3],P[3],C[3]);

endmodule
