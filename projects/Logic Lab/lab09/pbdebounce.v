`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:01:29 11/05/2010 
// Design Name: 
// Module Name:    pbdebounce 
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
module pbdebounce
(input wire clk,
input wire button,
output reg pbreg);

	reg [7:0] pbshift;
	wire clk_1ms;
	
	timer_1ms m0(clk, clk_1ms);
	always@(posedge clk_1ms) begin
		pbshift=pbshift<<1;
		pbshift[0]=button;
		if (pbshift==0)
			pbreg=0;
		if (pbshift==8'hFF)
			pbreg=1;
	end
endmodule

module timer_1ms
(input wire clk,
output reg clk_1ms);
	
	reg [15:0] cnt;
	initial begin
		cnt [15:0] <=0;
		clk_1ms <= 0;
	end
	always@(posedge clk)
		if(cnt>=25000) begin
			cnt<=0;
			clk_1ms <= ~clk_1ms;
			end
		else begin
			cnt<=cnt+1;
		end
endmodule
