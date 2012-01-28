`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:42:41 12/02/2010 
// Design Name: 
// Module Name:    m_gen_min 
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
module m_gen_min(clk_sec, clk_hour, min_low, min_high);
	input wire clk_sec;
	output reg clk_hour;
	output reg[3:0] min_low, min_high;
	reg [15:0] cnt;
	
	initial min_low<=0;
	initial min_high<=0;
	
	always @(posedge clk_sec) begin
		if (clk_hour == 1)
			clk_hour = 0;
		if (cnt == 59) begin
			cnt = 0;
			if (min_low == 9) begin
				min_low = 0; /* base 10 */
				if (min_high == 5) begin
					min_high = 0; /* base 6 */
					clk_hour = 1;
				end else
					min_high = min_high + 1;
			end else
				min_low = min_low + 1;
		end else
			cnt = cnt + 1;
	end
	
endmodule
