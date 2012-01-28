`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:15:30 04/15/2011 
// Design Name: 
// Module Name:    adder_32 
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
module add32(A,B,Cin,m,S,CF,OF);
    input wire [31:0] A,B;
	 input wire Cin,m;
	 output wire [31:0] S;
	 output wire CF,OF;
	 
	 wire t0,t1,t2,t3,t4,t5,t6,t7;
	 
	 ADD_4 A0(A[3:0],B[3:0],m,m,S[3:0],t0);
	 ADD_4 A1(A[7:4],B[7:4],t0,m,S[7:4],t1);
	 ADD_4 A2(A[11:8],B[11:8],t1,m,S[11:8],t2);
	 ADD_4 A3(A[15:12],B[15:12],t2,m,S[15:12],t3);
	 ADD_4 A4(A[19:16],B[19:16],t3,m,S[19:16],t4);
	 ADD_4 A5(A[23:20],B[23:20],t4,m,S[23:20],t5);
	 ADD_4 A6(A[27:24],B[27:24],t5,m,S[27:24],t6);
	 ADD_4 A7(A[31:28],B[31:28],t6,m,S[31:28],t7,OF);
	 
	 assign CF=t7^m;
	 
	 assign zero=~|S;
endmodule
