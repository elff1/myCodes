`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:14:07 04/15/2011 
// Design Name: 
// Module Name:    mux_5 
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
module mux5(
	input wire [4:0] A,
	input wire [4:0] B,
	input wire ctrl,
	output wire [4:0] S
    );
	assign S = (ctrl==0)?(A):(B);
endmodule
