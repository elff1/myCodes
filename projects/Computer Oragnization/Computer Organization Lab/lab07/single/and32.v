`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:25:17 04/17/2011 
// Design Name: 
// Module Name:    and32 
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
module and32(S,A,B);
    input wire [31:0] A;
	 input wire [31:0] B;
	 output wire [31:0] S;
	 
	 and(S[0],A[0],B[0]);
	 and(S[1],A[1],B[1]);
	 and(S[2],A[2],B[2]);
	 and(S[3],A[3],B[3]);
	 and(S[4],A[4],B[4]);
	 and(S[5],A[5],B[5]);
	 and(S[6],A[6],B[6]);
	 and(S[7],A[7],B[7]);
	 and(S[8],A[8],B[8]);
	 and(S[9],A[9],B[9]);
	 and(S[10],A[10],B[10]);
	 and(S[11],A[11],B[11]);
	 and(S[12],A[12],B[12]);
	 and(S[13],A[13],B[13]);
	 and(S[14],A[14],B[14]);
	 and(S[15],A[15],B[15]);
	 and(S[16],A[16],B[16]);
	 and(S[17],A[17],B[17]);
	 and(S[18],A[18],B[18]);
	 and(S[19],A[19],B[19]);
	 and(S[20],A[20],B[20]);
	 and(S[21],A[21],B[21]);
	 and(S[22],A[22],B[22]);
	 and(S[23],A[23],B[23]);
	 and(S[24],A[24],B[24]);
	 and(S[25],A[25],B[25]);
	 and(S[26],A[26],B[26]);
	 and(S[27],A[27],B[27]);
	 and(S[28],A[28],B[28]);
	 and(S[29],A[29],B[29]);
	 and(S[30],A[30],B[30]);
	 and(S[31],A[31],B[31]);

endmodule

