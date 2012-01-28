`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:10:49 03/16/2011 
// Design Name: 
// Module Name:    top_4bit 
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
module top_4bit(
	input wire clk,
	input wire [7:0]sw,
	output wire [3:0]anode,
	output wire [7:0]segment
);

	reg [3:0] A,B;
	wire [7:0] M;
	reg [15:0] disp_num;
	
	mul_4bit m0(A,B,M);
	display d0(clk,0,4'b1111,disp_num,4'b1111,anode,segment);

	
	always @* begin
		A = sw[3:0];
		B = sw[7:4];
		disp_num = {M,B,A};
	end
	
endmodule
