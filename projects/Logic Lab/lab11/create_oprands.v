`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:28:57 11/18/2010 
// Design Name: 
// Module Name:    create_oprands 
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
module create_oprands(
	input wire [7:0] switch,
	input wire [3:0] btn,
	input wire [15:0] reg_in3,
	output reg [15:0] op_out1,op_out2,
	output wire [15:0] reg_out3
);
	wire [15:0]out_shift1, out_shift2, out_inc1, out_inc2, reg_out1, reg_out2;
	reg [15:0] reg_in1, reg_in2;
	
	btn_increment m0(btn[3:0], switch[3:0], out_inc1, out_inc2);
	shift_reg_16 m1(btn[2:0], switch[3:0], switch[7:4], out_shift1, out_shift2);
	regfile_16 m2(btn[0], btn[1], switch[1:0], switch[7:4], reg_in1, reg_in2, reg_in3,
						reg_out1, reg_out2, reg_out3);
	
	always @* begin
		if(switch[1:0] == 2'b01)
		begin
			case(switch[3:2])
				2'b00:op_out1 = out_inc1;
				2'b01:op_out1 = out_shift1;
				default: if(btn[1] == 1'b1) op_out1 = reg_out1;
			endcase
			reg_in1 = op_out1;
		end
		else if(switch[1:0] == 2'b10)
		begin
			case(switch[3:2])
				2'b00:op_out2 = out_inc2;
				2'b01:op_out2 = out_shift2;
				default: if(btn[1] == 1'b1) op_out2 = reg_out2;
			endcase
			reg_in2 = op_out2;
		end
	end

endmodule
