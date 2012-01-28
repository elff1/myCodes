`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:55:29 04/15/2011 
// Design Name: 
// Module Name:    pc_plus4 
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
module pc_plus4(
	input wire [8:0] i_pc,
	output wire [8:0] o_pc
    );
	assign o_pc[8:0] = i_pc[8:0]+1;
endmodule
