`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:37:05 03/24/2011 
// Design Name: 
// Module Name:    mul_c4bit 
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
module mul_c4bit(A,B,M);
	input wire [3:0] A,B;
	output reg [7:0] M;

	reg E;
	reg [3:0] Ac;
	
	always @* begin
		M = {4'h0,B};
		Ac = ~A + 1;
		E = 0;
		repeat(4) begin
			if(E > M[0]) begin
				M[7:4] = M[7:4] + A;
			end
			else if(E < M[0])begin
				M[7:4] = M[7:4] + Ac;
			end
			E = M[0];
			M = M >> 1;
			M[7] = M[6];
		end
	end

endmodule
