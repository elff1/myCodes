`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:45:01 12/16/2010 
// Design Name: 
// Module Name:    register16 
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
module register16(clk, Di, Do );
	input wire clk;
	input wire [15:0] Di;
	output reg [15:0] Do;
	
	always @(posedge clk)
		Do <= Di;
endmodule
