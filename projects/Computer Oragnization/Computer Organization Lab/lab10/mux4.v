`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:32:30 04/17/2011 
// Design Name: 
// Module Name:    mux4 
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
module mux32_4_1(
	 output reg [31:0] result,
	 input wire [1:0] select,
    input wire [31:0] A,
	 input wire [31:0] B,
	 input wire [31:0] C,
	 input wire [31:0] D
    );
	 
	 always @(A or B or C or D or select)
	 case(select)
		2'b00:
			result=A;
		2'b01:
		   result=B;
		2'b10:
		   result=C;
		2'b11:
		   result=D;
	endcase
endmodule
