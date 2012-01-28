`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:45:27 12/02/2010 
// Design Name: 
// Module Name:    clock_24h 
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
module clock_24h(clk_sec,digit);
	input wire clk_sec;
	output wire[15:0] digit;
	wire clk_hour,clk_day;
	wire [3:0] hour_high,hour_low,min_high,min_low;
	
	m_gen_min MIN (clk_sec, clk_hour, min_low, min_high);
	m_gen_hour HOUR(clk_hour, clk_day, hour_low, hour_high);
	assign digit[15:12] = hour_high[3:0] ;
	assign digit[11:8] = hour_low[3:0] ;
	assign digit[7:4] = min_high[3:0] ;
	assign digit[3:0] = min_low[3:0] ;
endmodule
