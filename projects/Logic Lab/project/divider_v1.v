`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    23:11:00 12/26/2010 
// Design Name: 
// Module Name:    Divisor_V1 
// Project Name:   8-to-16bit Unsigned Integer Divider
// Target Devices: Spartan-3 Board & Kits
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
module divider_v1(
    input CLK_1ms,
    input [15:0] DIVIDEND,        // dividend input
    input [7:0] DIVISOR,          // divisor input
    output reg [7:0] QUOTIENT,    // quotient output
    output reg [7:0] REMAINDER,   // remainder output
    output reg DZ,                // divided by zero flag
    output reg DO                 // divider overflow flag	 
    );

	 initial begin
	    DZ = 1'b0;
		 DO = 1'b0;
		 QUOTIENT = 0;
		 REMAINDER = 0;
	 end

    always @(posedge CLK_1ms) begin
       QUOTIENT = DIVIDEND/32 + 1;
	    REMAINDER = DIVIDEND%256;
		 if(QUOTIENT > 128)DO = 1;
		 else DO = 0;
		 if(DIVISOR == 0)DZ = 1;
		 else DZ = 0;
	 end
endmodule
