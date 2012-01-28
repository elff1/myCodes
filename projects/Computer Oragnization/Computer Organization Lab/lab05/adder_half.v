`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:23:00 03/15/2011 
// Design Name: 
// Module Name:    adder_half 
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
module adder_half(x,y,p,g);
	input wire x,y;
	output wire p,g;
	
	xor (p,x,y);
	and (g,x,y);

endmodule
