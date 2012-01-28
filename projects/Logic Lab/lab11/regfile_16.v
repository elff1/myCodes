`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:35:00 12/16/2010 
// Design Name: 
// Module Name:    regfile_16 
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
module regfile_16 (input wire wclk, rclk, input wire [1:0]switch,	input wire [3:0]address, 
	input wire [15:0]op1_in, input wire [15:0]op2_in, input wire [15:0]result_in,
	output reg [15:0]op1_out, output reg [15:0]op2_out, output reg [15:0]result_out
	);
	
	wire [15:0] op_o;
	wire [1:0] btn_op1;
	wire [1:0] btn_op2;
	reg [15:0] op_in;
	
	regfile rf(wclk, rclk, address, op_in, op_o);
	always @* begin
		if(switch[1:0] == 2'b01) begin
			op1_out = op_o;
			op_in = op1_in;
		end
		else if(switch[1:0] == 2'b10) begin
			op2_out = op_o;
			op_in = op2_in;
		end
		else if(switch[1:0] == 2'b00) begin
			result_out = op_o;
			op_in = result_in;
		end
	end
endmodule
