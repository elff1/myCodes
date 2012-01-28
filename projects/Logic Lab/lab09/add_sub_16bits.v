`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:29:39 11/18/2010 
// Design Name: 
// Module Name:    add_sub_16bits 
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
module add_sub_16bits(
	input wire [16:1] A,B,
	input wire Ctr,
	output [16:1] S,
	output wire Co
);

	wire [16:1] Bo;
	wire [15:1] Ctemp;
	
	assign Bo = {16{Ctr}} ^ B;
	adder_1bit A1_1(A[1], Bo[1], Ctr, S[1], Ctemp[1]),
				A1_2(A[2], Bo[2], Ctemp[1], S[2], Ctemp[2]),
				A1_3(A[3], Bo[3], Ctemp[2], S[3], Ctemp[3]),
				A1_4(A[4], Bo[4], Ctemp[3], S[4], Ctemp[4]),
				A1_5(A[5], Bo[5], Ctemp[4], S[5], Ctemp[5]),
				A1_6(A[6], Bo[6], Ctemp[5], S[6], Ctemp[6]),
				A1_7(A[7], Bo[7], Ctemp[6], S[7], Ctemp[7]),
				A1_8(A[8], Bo[8], Ctemp[7], S[8], Ctemp[8]),
				A1_9(A[9], Bo[9], Ctemp[8], S[9], Ctemp[9]),
				A1_10(A[10], Bo[10], Ctemp[9], S[10], Ctemp[10]),
				A1_11(A[11], Bo[11], Ctemp[10], S[11], Ctemp[11]),
				A1_12(A[12], Bo[12], Ctemp[11], S[12], Ctemp[12]),
				A1_13(A[13], Bo[13], Ctemp[12], S[13], Ctemp[13]),
				A1_14(A[14], Bo[14], Ctemp[13], S[14], Ctemp[14]),
				A1_15(A[15], Bo[15], Ctemp[14], S[15], Ctemp[15]),
				A1_16(A[16], Bo[16], Ctemp[15], S[16], Co);

endmodule
