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
	wire [63:0] S1;
	reg [32:0] DB;
	wire [31:0] S2;
	reg FB, FA;
	reg [6:0] cnt;
	
	//adder_64 a0(DA[63:0], {{63{1'b0}},FA}, 0, S1,);
	//adder_32 a1(DB, {{31{1'b0}},FB}, 0, S2,);
	
	initial begin
		Q = 0;
		R = 0;
		DZ = 0;
		DO = 0;
	end
	
	always @(A or B)begin
		cnt = 7'b1000000;
		
		FA = A[31];
		if(FA)begin
			DA[63:0] = ~A;
			DA[63:0] = DA[63:0] + FA;//S1;//
		end
		DA[96:64] = {33{1'b0}};
		
		FB = B[31];
		if(FB)begin
			DB[31:0] = ~B;
			DB[31:0] = DB[31:0] + FB;//S2;//
		end
		DB[32] = 0;
	end
	
	always @(posedge clk)begin
		if(cnt > 0)begin
			DA = DA << 1;
			if(DA[96:64] >= DB)begin
				DA[96:64] = DA[96:64] - DB;
				DA[0] = 1;
			end
			cnt = cnt - 1;
		end else if(DB == 0)
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
