`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:54:14 03/30/2011 
// Design Name: 
// Module Name:    div_32f 
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
module div_32f(x,y,z,zo);
	input wire [31:0] x,y;
	output reg [31:0] z;
	output reg zo;
	
	reg xs, ys, zs;
	reg [7:0] xe, ye, ze;
	reg [24:0] xm, ym;
	reg [23:0] zm;
	
//	initial begin
//	end
//	
//	always @(x or y)begin
//	end
	
	always @* begin
		z = {32{1'b0}};
		xs = x[31];
		xe = x[30:23];
		xm = {0,1,x[22:0]};
		ys = y[31];
		ye = y[30:23];
		ym = {0,1,y[22:0]};
		zo = 0;
		zs = xs ^ ys;
		if(xe > ye)begin
			ze = xe - ye;
			if(ze > 128) zo = 1;
			ze = ze + 127;
		end else begin
			ze = ye - xe;
			if(ze > 127) zo = 1;
			ze = 127 - ze;
		end
		
		zm = {24{1'b0}};
		repeat(24)begin
			zm = zm << 1;
			if(xm >= ym)begin
				xm = xm - ym;
				zm[0] = 1;
			end
			xm = xm << 1;
		end
		if(zm[23] == 0)begin
			zm = zm << 1;
			ze = ze - 1;
		end
		
		if(y == 0)begin
			if(x == 0) z = {0,{31{1'b1}}};
			else if(xs) z[31:23] = {9{1'b1}};
			else z[30:23] = {8{1'b1}};
		end else if(x == 0) z = x;
		else z = {zs,ze,zm[22:0]};
	end

endmodule