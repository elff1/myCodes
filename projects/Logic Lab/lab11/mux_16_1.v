`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:08:03 12/17/2010 
// Design Name: 
// Module Name:    mux_16_1 
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
module mux_16_1(rclk, address,
		regQ0, regQ1, regQ2, regQ3,
		regQ4, regQ5, regQ6, regQ7,
		regQ8, regQ9, regQ10,regQ11,
		regQ12,regQ13,regQ14,regQ15,
		Dataout
);
input wire[3:0] address;
input wire rclk;
input wire [15:0] regQ0, regQ1, regQ2, regQ3,
			regQ4, regQ5, regQ6, regQ7,
			regQ8, regQ9, regQ10,regQ11,
			regQ12,regQ13,regQ14,regQ15;
output reg[15:0] Dataout;
	 
	always @*begin
		if(rclk==1'b1)
			case(address[3:0])
				4'b0000:Dataout=regQ0;
				4'b0001:Dataout=regQ1;
				4'b0010:Dataout=regQ2;
				4'b0011:Dataout=regQ3;
				4'b0100:Dataout=regQ4;
				4'b0101:Dataout=regQ5;
				4'b0110:Dataout=regQ6;
				4'b0111:Dataout=regQ7;
				4'b1000:Dataout=regQ8;
				4'b1001:Dataout=regQ9;
				4'b1010:Dataout=regQ10;
				4'b1011:Dataout=regQ11;
				4'b1100:Dataout=regQ12;
				4'b1101:Dataout=regQ13;
				4'b1110:Dataout=regQ14;
				4'b1111:Dataout=regQ15;
			endcase
		else
			Dataout=16'h0000;
	end

endmodule
