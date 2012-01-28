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
module div_64(clk,A,B,Q,R,DZ,DO,cnt);
	input wire clk;
	input wire [63:0] A;
	input wire [31:0] B;
	output reg [31:0] Q;
	output reg [31:0] R;
	output reg DZ, DO;
	output reg [5:0] cnt;
	
	reg [64:0] DA;
	wire [63:0] S1;
	reg [32:0] DB;
	wire [31:0] S2;
	reg FB, FA;
	
	//adder_64 a0(DA[63:0], {{63{1'b0}},FA}, 0, S1,);
	//adder_32 a1(DB, {{31{1'b0}},FB}, 0, S2,);
	
	initial begin
		Q = 0;
		R = 0;
		DZ = 0;
		DO = 0;
		cnt = 6'b000000;
	end
	
	always @(A or B)begin
		cnt = 6'b100000;
		
		FA = A[63];
		if(FA)begin
			DA[63:0] = ~A;
			DA[63:0] = DA[63:0] + FA;//S1;//
		end
		else
			DA[63:0] = A;
		DA[64] = 0;
		
		FB = B[31];
		if(FB)begin
			DB[31:0] = ~B;
			DB[31:0] = DB[31:0] + FB;//S2;//
		end
		else
			DB[31:0] = B;
		DB[32] = 0;
		
		if(DA[63:32] >= DB[31:0])begin
			DO = 1;
			DZ = 0;
			Q = 0;
			R = 0;
		end 
	end
	
	always @(posedge clk)begin
		if(DB == 0)
		begin
			Q = 0;
			R = 0;
			DZ = 1;
			DO = 0;
		end else if(!DO) if(cnt > 0)begin
			DA = DA << 1;
			if(DA[64:32] >= DB)begin
				DA[64:32] = DA[64:32] - DB;
				DA[0] = 1;
			end
			cnt = cnt - 6'b000001;
		end else begin
			DO = 0;
			DZ = 0;
			Q = DA[31:0];
			R = DA[63:32];
		end
	end

endmodule
