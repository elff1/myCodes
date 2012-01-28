`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:12:35 11/25/2010 
// Design Name: 
// Module Name:    counter_16bit_rev 
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
module counter_16bit_rev(clk, s, cnt);
	input wire clk, s;
	output reg [15:0] cnt;

	always @ (posedge clk) begin
		if (s)
			cnt <= cnt + 1;
		else
			cnt <= cnt - 1;
	end
endmodule
