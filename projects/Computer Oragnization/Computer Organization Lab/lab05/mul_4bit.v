`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:50:39 03/22/2011 
// Design Name: 
// Module Name:    mul_8bit 
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
module mul_4bit(clk,A,B,M);
	input wire clk;
	input wire [3:0] A,B;
	output reg [7:0] M;
	
	reg [2:0]cnt;
	wire Co;
	//reg C;
	wire [3:0] So;
	//reg [3:0] S;

	adder_4bit a0(M[7:4],A,1'b0,So,Co);

	initial begin
		cnt = 3'b100;
		M = {4'h0,B};
	end
		
	always @(A or B)begin
		cnt = 3'b100;
		M = {4'h0,B};
	end
	
	always @(clk) begin
		if(cnt > 0)
			begin
//				if(M[0]) begin
//					S = So;
//					C = Co;
//					M[7:4] = So;
//					M = M >> 1;
//					M[7] = C;
//				end else begin
//					M = M >> 1;
//				end
				M[7:0] <= M[0] ? {Co,So,M[3:1]} : {1'b0, M[7:1]};
				cnt = cnt - 1;
			end
	end

endmodule
