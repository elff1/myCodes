`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    19:57:37 12/27/2010 
// Design Name: 
// Module Name:    divisor_v2 
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
module divider_v2(
    input CLK_1ms,
    input [15:0] DIVIDEND,        // dividend input
    input [7:0] DIVISOR,          // divisor input
    output reg [7:0] QUOTIENT,    // quotient output
    output reg [7:0] REMAINDER,   // remainder output
    output reg DZ,                // divided by zero flag
    output reg DO                 // divider overflow flag	 
    );

    wire [15:0] dividend_tmp;
	 wire [7:0] divisor_tmp;
	 wire [15:0] quotient_tmp;
	 wire [7:0] fractional_tmp;

    assign dividend_tmp = DIVIDEND;
	 assign divisor_tmp = DIVISOR;
	 
	 initial begin
	    QUOTIENT = 0;
		 REMAINDER = 0;
		 DZ = 0;
		 DO = 0;
	 end
	 
	 divider_ip Divider_IP (
		 .clk(CLK_1ms),
		 .rfd(),
		 .dividend(dividend_tmp), // Bus [15 : 0] 
		 .divisor(divisor_tmp), // Bus [7 : 0] 
		 .quotient(quotient_tmp), // Bus [15 : 0] 
		 .remainder(fractional_tmp)); // Bus [7 : 0] 
		
	 always @(posedge CLK_1ms) begin
	    if(DIVISOR == 0) begin
		    DZ = 1; DO = 0;
		    QUOTIENT = 0;
			 REMAINDER = 0;
		 end else if(quotient_tmp > 255) begin
		    DO = 1; DZ = 0;
		    QUOTIENT = quotient_tmp[7:0];
			 REMAINDER = fractional_tmp;
		 end else begin
		    DO = 0; DZ = 0;
		    QUOTIENT = quotient_tmp[7:0];
			 REMAINDER = fractional_tmp;		    
		 end
	 end
endmodule
