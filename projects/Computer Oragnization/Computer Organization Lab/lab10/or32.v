`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:28:02 04/17/2011 
// Design Name: 
// Module Name:    or32 
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
module or32(
    output wire [31:0] S,
	 input wire [31:0] A,
	 input wire [31:0] B
    );
	
	 or(S[0],A[0],B[0]);
	 or(S[1],A[1],B[1]);
	 or(S[2],A[2],B[2]);
	 or(S[3],A[3],B[3]);
	 or(S[4],A[4],B[4]);
	 or(S[5],A[5],B[5]);
	 or(S[6],A[6],B[6]);
	 or(S[7],A[7],B[7]);
	 or(S[8],A[8],B[8]);
	 or(S[9],A[9],B[9]);
	 or(S[10],A[10],B[10]);
	 or(S[11],A[11],B[11]);
	 or(S[12],A[12],B[12]);
	 or(S[13],A[13],B[13]);
	 or(S[14],A[14],B[14]);
	 or(S[15],A[15],B[15]);
	 or(S[16],A[16],B[16]);
	 or(S[17],A[17],B[17]);
	 or(S[18],A[18],B[18]);
	 or(S[19],A[19],B[19]);
	 or(S[20],A[20],B[20]);
	 or(S[21],A[21],B[21]);
	 or(S[22],A[22],B[22]);
	 or(S[23],A[23],B[23]);
	 or(S[24],A[24],B[24]);
	 or(S[25],A[25],B[25]);
	 or(S[26],A[26],B[26]);
	 or(S[27],A[27],B[27]);
	 or(S[28],A[28],B[28]);
	 or(S[29],A[29],B[29]);
	 or(S[30],A[30],B[30]);
	 or(S[31],A[31],B[31]);
endmodule
