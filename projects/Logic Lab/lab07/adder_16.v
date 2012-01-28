`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:14:12 11/18/2010 
// Design Name: 
// Module Name:    adder_16 
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
module top(
	input wire clk, 
	input wire [3:0]btn_in, 
	input wire[1:0]switch, 
	output wire [3:0]anode, 
	output wire [7:0]segment
);
	
	//variable definition: op1, op2,disp_num¡­
	reg [15:0] display_num;
	wire [15:0] op1,op2;
	wire [3:0] btn_out;
	wire [15:0] result;

	pbdebounce b0(clk, btn_in[0], btn_out[0]);
	pbdebounce b1(clk, btn_in[1], btn_out[1]);
	pbdebounce b2(clk, btn_in[2], btn_out[2]);
	pbdebounce b3(clk, btn_in[3], btn_out[3]);

	display m0(clk, 0, display_num, 4'b1111, anode, segment); //display module
	calculate_result m1(btn_out[3:0], op1, op2, result); //calculate result
	create_oprands m2(switch[1:0], btn_out[3:0], op1, op2); //generate op1/op2
	//pbdebouce¡­

	always @* begin
		case (switch)
			2'b01: display_num = op1; //operand 1
			2'b10: display_num = op2; //operand 2
			2'b00: display_num = result; //result
		endcase
	end

endmodule
