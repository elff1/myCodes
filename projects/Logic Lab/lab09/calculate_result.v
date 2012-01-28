`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:27:02 11/18/2010 
// Design Name: 
// Module Name:    calculate_result 
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
module calculate_result(
	input wire [3:0] btn,
	input wire [15:0] op1,
	input wire [15:0] op2,
	output reg [15:0] result
);
	
	wire [15:0] add_sub_result;
	wire co;

	add_sub_16bits m0(op1, op2, btn[1], add_sub_result, co);
	
	always @(btn) begin
		if(btn[0] == 1 || btn[1] == 1)
			result = add_sub_result;
		if(btn[2] == 1)
			result = op1 & op2;
		if(btn[3] == 1)
			result = op1 | op2;
	end

endmodule
