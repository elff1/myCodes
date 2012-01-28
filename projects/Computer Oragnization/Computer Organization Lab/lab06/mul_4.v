`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:09:45 04/06/2011 
// Design Name: 
// Module Name:    mul_4 
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
module mul(P,A,B);input wire [3:0] A;input wire [3:0] B;output reg [7:0] P;reg [8:0] I;
reg [3:0] nA;

initial begin
	P = {8{1'b0}};
endalways@(A or B) begin	I={4'b0000,B,1'b0};
	nA=(~A[3:0])+1;	repeat(4)	begin		case (I[1:0])			2'b01:I[8:5]=I[8:5]+A;			2'b10:I[8:5]=I[8:5]+nA;		endcase		I={I[8],I[8:1]};	end	P[7:0]=I[8:1];endendmodule
