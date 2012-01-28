`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:32:21 06/01/2011 
// Design Name: 
// Module Name:    slowDown 
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
module slowDown(clk, dclk);
	input wire clk;
	output reg dclk;
	
	reg [31:0] cnt;
	
	initial begin
		cnt = 0;
		dclk = 0;
	end
	
	always @(posedge clk)begin
		cnt = cnt + 1;
		if(cnt == 10000000)begin
			cnt = 0;
			dclk = ~dclk;
		end
	end

endmodule
