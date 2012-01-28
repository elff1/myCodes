`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:43:16 12/02/2010 
// Design Name: 
// Module Name:    m_gen_hour 
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
module m_gen_hour(clk_hour, clk_day, hour_low, hour_high);
	input wire clk_hour;
	output reg clk_day;
	output reg[3:0] hour_low, hour_high;
	
	initial hour_low<=0;
	initial hour_high<=0;
	
	always @(posedge clk_hour)
		if (hour_low == 3 && hour_high == 2) begin
			hour_low = 0;
			hour_high = 0;
			clk_day = ~clk_day;
		end else if (hour_low == 9) begin
			hour_low = 0;
			hour_high = hour_high + 1;
		end else
			hour_low = hour_low + 1;			
endmodule
