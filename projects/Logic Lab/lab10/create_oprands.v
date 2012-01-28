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
	output reg [15:0] op_out1,op_out2
);
	wire [15:0]out_shift1, out_shift2, out_inc1, out_inc2;
	
	btn_increment m0(btn[3:0], switch[1:0], out_inc1, out_inc2);
	shift_reg_16 m1(btn[2:0], switch[3:0], switch[7:4], out_shift1, out_shift2);
	
	always @* begin
		if(switch[1:0] == 2'b01)
			case(switch[3:2])
			2'b00:op_out1 = out_inc1;
			2'b01:op_out1 = out_shift1;
			endcase
		else if(switch[1:0] == 2'b10)
			case(switch[3:2])
			2'b00:op_out2 = out_inc2;
			2'b01:op_out2 = out_shift2;
			endcase
	end

endmodule

module btn_increment(
	input wire [3:0] btn,
	input wire [1:0] switch,
	output reg [15:0] op1,op2
);
	initial op1 <= 16'b0110_0000_0000_0000; //op1,op2³õÊ¼»¯
	initial op2 <= 16'b0110_0000_0000_0000;
	
	always @(posedge btn[0])begin
		if(switch == 2'b01) op1[ 3: 0]<= op1[ 3: 0] + 1'd1;
		else if(switch == 2'b10) op2[ 3: 0]<= op2[ 3: 0] + 1'd1;
	end

	always @(posedge btn[1])begin
		if(switch == 2'b01) op1[ 7: 4]<= op1[ 7: 4] + 1'd1;
		else if(switch == 2'b10) op2[ 7: 4]<= op2[ 7: 4] + 1'd1;
	end

	always @(posedge btn[2])begin
		if(switch == 2'b01) op1[ 11: 8]<= op1[ 11: 8] + 1'd1;
		else if(switch == 2'b10) op2[ 11: 8]<= op2[ 11: 8] + 1'd1;
	end

	always @(posedge btn[3])begin
		if(switch == 2'b01) op1[ 15: 12]<= op1[ 15: 12] + 1'd1;
		else if(switch == 2'b10) op2[ 15: 12]<= op2[ 15: 12] + 1'd1;
	end
	
endmodule
