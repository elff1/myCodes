`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:48:28 12/09/2010 
// Design Name: 
// Module Name:    shift_reg 
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

module shift_reg(clk, S, s_in, p_in, Q);
input wire clk, S, s_in;
input wire [15:0] p_in;
output wire [15:0] Q;
wire [15:0] D;
wire nS;
	
	shift_reg_8 m0(clk, S, s_in, p_in[15:8], Q[15:8]);
	shift_reg_8 m1(clk, S, Q[8], p_in[7:0], Q[7:0]);
	
endmodule

module shift_reg_8(clk, S, s_in, p_in, Q);
input wire clk, S, s_in;
input wire [7:0] p_in;
output wire [7:0] Q;
wire [7:0] D;
wire nS;

FD FDQ0(.C(clk), .D(D[0]), .Q(Q[0])),
	FDQ1(.C(clk), .D(D[1]), .Q(Q[1])),
	FDQ2(.C(clk), .D(D[2]), .Q(Q[2])),
	FDQ3(.C(clk), .D(D[3]), .Q(Q[3])),
	FDQ4(.C(clk), .D(D[4]), .Q(Q[4])),
	FDQ5(.C(clk), .D(D[5]), .Q(Q[5])),
	FDQ6(.C(clk), .D(D[6]), .Q(Q[6])),
	FDQ7(.C(clk), .D(D[7]), .Q(Q[7]));
	
OR2 D0_L(.I0(L_0), .I1(R_0), .O(D[0])),
	D1_L(.I0(L_1), .I1(R_1), .O(D[1])),
	D2_L(.I0(L_2), .I1(R_2), .O(D[2])),
	D3_L(.I0(L_3), .I1(R_3), .O(D[3])),
	D4_L(.I0(L_4), .I1(R_4), .O(D[4])),
	D5_L(.I0(L_5), .I1(R_5), .O(D[5])),
	D6_L(.I0(L_6), .I1(R_6), .O(D[6])),
	D7_L(.I0(L_7), .I1(R_7), .O(D[7]));
	
AND2 L0_L(.I0(Q[1]), .I1(nS), .O(L_0)),
	L1_L(.I0(Q[2]), .I1(nS), .O(L_1)),
	L2_L(.I0(Q[3]), .I1(nS), .O(L_2)),
	L3_L(.I0(Q[4]), .I1(nS), .O(L_3)),
	L4_L(.I0(Q[5]), .I1(nS), .O(L_4)),
	L5_L(.I0(Q[6]), .I1(nS), .O(L_5)),
	L6_L(.I0(Q[7]), .I1(nS), .O(L_6)),
	L7_L(.I0(s_in), .I1(nS), .O(L_7));
	
AND2 R0_L(.I0(p_in[0]), .I1(S), .O(R_0)),
	R1_L(.I0(p_in[1]), .I1(S), .O(R_1)),
	R2_L(.I0(p_in[2]), .I1(S), .O(R_2)),
	R3_L(.I0(p_in[3]), .I1(S), .O(R_3)),
	R4_L(.I0(p_in[4]), .I1(S), .O(R_4)),
	R5_L(.I0(p_in[5]), .I1(S), .O(R_5)),
	R6_L(.I0(p_in[6]), .I1(S), .O(R_6)),
	R7_L(.I0(p_in[7]), .I1(S), .O(R_7));
	
INV nS_L(.I(S), .O(nS));
endmodule
