`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:35:42 12/09/2010 
// Design Name: 
// Module Name:    shift_reg_16 
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

module shift_reg_16(
	input wire [2:0]btn,
	input wire [3:0]switch,
	input wire [3:0]p_in, 
	output reg [15:0]op_out1, 
	output reg [15:0]op_out2
);
	wire [0:15]Q1,Q2;	
	wire clk1 = btn[1]&switch[2]&~switch[3]&switch[0]&~switch[1];
	wire clk2 = btn[1]&switch[2]&~switch[3]&switch[1]&~switch[0];
	
	shift_reg sr1(clk1, btn[2], btn[0], {4{p_in[0],p_in[1],p_in[2],p_in[3]}}, Q1);
	shift_reg sr2(clk2, btn[2], btn[0], {4{p_in[0],p_in[1],p_in[2],p_in[3]}}, Q2);
	
	always @* begin
		if(switch == 4'b0101) op_out1[15:0] = Q1[0:15];
		else if(switch == 4'b0110) op_out2[15:0] = Q2[0:15];
	end
	
endmodule
