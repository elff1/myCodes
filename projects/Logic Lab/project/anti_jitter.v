`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    21:28:42 12/26/2010 
// Design Name: 
// Module Name:    anti_jitter 
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
module anti_jitter(
    input CLK_1ms,
    input [1:0] I_BTN,
    output reg [1:0] BTN
    );
	 
	 reg [3:0] cnt_aj = 0;

	 initial
	    BTN[1:0] = 2'b00;
	 
	 always @(posedge CLK_1ms) begin
	    if(I_BTN == BTN) cnt_aj <= 0;
	    else cnt_aj <= cnt_aj + 1;
		 if((cnt_aj == 4'b1111) && (I_BTN != BTN))BTN <= I_BTN;
	 end
endmodule
