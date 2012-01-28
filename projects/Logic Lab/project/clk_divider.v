`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Zhejiang University, 
// Engineer: Donghui Wang
// 
// Create Date:    15:43:07 12/26/2010 
// Design Name:    
// Module Name:    clk_divider 
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
module clk_divider(
   input CLK,           // 50MHz Clock, T = 20ns = 1/50 us = 1/50000 ms
   output reg CLK_1ms,  // 50% Duty Cycle, clock period 1ms
   output reg CLK_512ms // 50% Duty Cycle, clock period 512ms
   );

   reg [8:0]  cnt9 = 0;
   reg [15:0] cnt16= 0;   
   
	initial 
       CLK_512ms = 1'b0;
    
   always @(posedge CLK_1ms) begin
      if (cnt9 <= 256) CLK_512ms <= 0;
		else CLK_512ms <= 1;
		cnt9 <= cnt9 + 1;
      //CLK_512ms = CLK_512ms ^ (&cnt8); 
   end  
	
   always @(posedge CLK)begin
  	  if (cnt16 >= 50000) begin
		  CLK_1ms <= 0;
		  cnt16 <= 0; end
	  else if (cnt16 < 25000) begin
		  CLK_1ms <= 0;
		  cnt16 <= cnt16 + 1; end
	  else if ((cnt16 >= 25000) && (cnt16 < 50000)) begin	
			CLK_1ms <= 1;
			cnt16 <= cnt16 + 1; end
   end		
endmodule
