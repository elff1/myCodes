`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:14:37 04/15/2011 
// Design Name: 
// Module Name:    mux_32 
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
module mux32(
	input wire [31:0] A,
	input wire [31:0] B,
	input wire ctrl,
	output wire [31:0] S
    );
	assign S = (ctrl==0)?(A):(B);
endmodule
