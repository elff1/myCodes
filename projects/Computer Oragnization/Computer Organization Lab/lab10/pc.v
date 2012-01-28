`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:09:29 04/17/2011 
// Design Name: 
// Module Name:    pc 
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
module pc(
	input wire clk,
	input wire rst,
	input wire [8:0] in,
	output wire [8:0] out
	);
	wire [8:0] t;
	assign out = rst?9'b111111111:t;
	next n(clk,in,t);
endmodule

module next(
	input wire clk,
	input wire [8:0] i,
	output reg [8:0] o
	);
	always @(posedge clk)
		o<=i;
endmodule
