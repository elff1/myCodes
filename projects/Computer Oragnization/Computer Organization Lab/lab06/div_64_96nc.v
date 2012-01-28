`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:33:15 03/28/2011 
// Design Name: 
// Module Name:    divider_32 
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
module div_64(clk,A,B,Q,R,DZ,DO);
	input wire clk;
	input wire [63:0] A;
	input wire [31:0] B;
	output reg [31:0] Q;
	output reg [31:0] R;
	output reg DZ, DO;
	
	reg [96:0] DA;
	reg [32:0] DB;
	reg FB, FA;

	initial begin
		Q = 0;
		R = 0;
		DZ = 0;
		DO = 0;
	end

	always @(posedge clk)begin
		FA = A[63];
		if(FA)begin
			DA[63:0] = ~A;
			DA[63:0] = DA[63:0] + FA;
		end
		else
			DA[63:0] = A;
		DA[96:64] = {33{1'b0}};
		
		FB = B[31];
		if(FB)begin
			DB[31:0] = ~B;
			DB[31:0] = DB[31:0] + FB;
		end
		else
			DB[31:0] = B;
		DB[32] = 0;
		
		repeat(64)begin
			DA = DA << 1;
			if(DA[96:64] >= DB)begin
				DA[96:64] = DA[96:64] - DB;
				DA[0] = 1;
			end
		end
		
		if(DB == 0)
		begin
			Q = 0;
			R = 0;
			DZ = 1;
			DO = 0;
		end else if(DA[63:32] > 0)begin
			DO = 1;
			DZ = 0;
			Q = DA[31:0];
			R = DA[95:64];
		end else begin
			DO = 0;
			DZ = 0;
			Q = DA[31:0];
			R = DA[95:64];
		end
	end

endmodule
