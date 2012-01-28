`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:53:15 04/17/2011 
// Design Name: 
// Module Name:    mux9_2_1 
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
module mux9(
	input wire [8:0] A,
	input wire [8:0] B,
	input wire ctrl,
	output wire [8:0] S
    );
	assign S=(ctrl==0)?A:B;
endmodule
