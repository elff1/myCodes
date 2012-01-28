`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:06:51 04/17/2011 
// Design Name: 
// Module Name:    control 
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
module control(rst,i_instr,o_aluop,o_regdst,o_jump,o_branch,o_memread,o_memtoreg,o_memwrite,o_alusrc,o_regwrite,o_selectzero);
	input [5:0] i_instr;
	input rst;
	output [1:0] o_aluop;
	output o_regdst;
	output o_branch;
	output o_jump;
	output o_memread;
	output o_memtoreg;
	output o_memwrite;
	output o_alusrc;
	output o_regwrite;
	output o_selectzero;
	
	assign o_regdst = (~i_instr[5] & ~i_instr[4] & ~i_instr[3] & ~i_instr[2] & ~i_instr[1] & ~i_instr[0]) & ~rst;
	assign o_branch = (~i_instr[5] & ~i_instr[4] & ~i_instr[3] & i_instr[2] & ~i_instr[1]) & ~rst;
	assign o_jump = (~i_instr[5] & ~i_instr[4] & ~i_instr[3] & ~i_instr[2] & i_instr[1] & ~i_instr[0]) & ~rst;
	assign o_memread = (i_instr[5] & ~i_instr[4] & ~i_instr[3] & ~i_instr[2] & i_instr[1] & i_instr[0]) & ~rst;
	assign o_memtoreg = (i_instr[5] & ~i_instr[4] & ~i_instr[3] & ~i_instr[2] & i_instr[1] & i_instr[0]) & ~rst;
	assign o_aluop[1] = (~i_instr[5] & ~i_instr[4] & ~i_instr[3] & ~i_instr[2] & ~i_instr[1] & ~i_instr[0]) & ~rst;
	assign o_aluop[0] = (~i_instr[5] & ~i_instr[4] & ~i_instr[3] & i_instr[2] & ~i_instr[1]) & ~rst;
	assign o_memwrite = (i_instr[5] & ~i_instr[4] & i_instr[3] & ~i_instr[2] & i_instr[1] & i_instr[0]) & ~rst;
	assign o_alusrc = ((i_instr[5] & ~i_instr[4] & ~i_instr[2] & i_instr[1] & i_instr[0])|(~i_instr[5]&~i_instr[4]&i_instr[3]&~i_instr[2]&~i_instr[1]&~i_instr[0])) & ~rst;
	assign o_regwrite = (~i_instr[4] & ~i_instr[3] & ~i_instr[2]) & ~rst;
	assign o_selectzero = (~i_instr[5] & ~i_instr[4] & ~i_instr[3] & i_instr[2] & ~i_instr[1] & i_instr[0]) & ~rst;
endmodule
