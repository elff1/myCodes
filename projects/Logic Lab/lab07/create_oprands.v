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
	input wire [1:0] switch,
	input wire [3:0] btn,
	output reg [15:0] op1,op2
);

	initial op1 <= 16'b1010_1011_1100_1101; //op1,op2³õÊ¼»¯
	initial op2 <= 16'b1010_1011_1100_1101;

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
