`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:12:50 10/29/2010 
// Design Name: 
// Module Name:    top 
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
module top(input wire C, B, A, G, G2A, G2B,output wire Y);

	wire [7:0] T;
	
	decoder_3_8  INSTANCE(C, B, A, G, G2A,G2B, T);
	assign Y = !( T[1] & T[2] & T[4] & T[7]);

endmodule

